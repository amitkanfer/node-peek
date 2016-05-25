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

    int res = recv(fd, argp, buffer_size, MSG_PEEK | MSG_DONTWAIT);

    if (res == -1) {
        info.GetReturnValue().Set(-errno);
        return;
    }
 
    info.GetReturnValue().Set(res);
}

void InitAll(Local<Object> exports) {
    exports->Set(Nan::New("peek").ToLocalChecked(),
                 Nan::New<FunctionTemplate>(Peek)->GetFunction());
}

NODE_MODULE(peek, InitAll)

