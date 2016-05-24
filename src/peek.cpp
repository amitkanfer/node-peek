#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "nan.h"

#define MIN(x,y) ((x) < (y) ? (x) : (y))

using namespace v8;
using namespace node;

NAN_METHOD(Peek) {
    Nan::HandleScope scope;    
    int length = info.Length();
    assert(length == 3);

    if (!info[0]->IsInt32()) {
        Nan::ThrowTypeError("Argument 0 Must be an Integer");
    }

    if (!info[1]->IsUint32()) {
        Nan::ThrowTypeError("Argument 1 Must be an Integer");
    }

    Local<Object> buf = info[2]->ToObject();
    if (!Buffer::HasInstance(buf)) {
        Nan::ThrowTypeError("Argument 2 Must be a Buffer");
    }

    void* argp = Buffer::Data(buf);
    int fd = info[0]->Int32Value();
    int buffer_size = info[1]->IntegerValue();
    int bytes_available = 0;

    int res = ioctl(fd, FIONREAD, &bytes_available);
    if (res == -1) {
        info.GetReturnValue().Set(-errno);
        return;
    }

    int bytes2read = MIN(bytes_available, buffer_size);
    res = recv(fd, argp, bytes2read, MSG_PEEK);
    info.GetReturnValue().Set(res);
}

void InitAll(Local<Object> exports) {
    exports->Set(Nan::New("peek").ToLocalChecked(),
                 Nan::New<FunctionTemplate>(Peek)->GetFunction());
}

NODE_MODULE(peek, InitAll)

