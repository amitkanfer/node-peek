var peek = require('bindings')('peek.node').peek;

module.exports = function(fd, size, argp) {
    var ret = peek(fd, size, argp);
    if (ret < 0) {
        var e = new Error('peek ' + ret);
        e.errno = e.code = ret;
        e.syscall = peek;
        throw e;
    }

    return ret;
};
