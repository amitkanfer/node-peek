var peek = require('bindings')('peek.node').peek;

module.exports = function(fd, size, argp) {
    return peek(fd, size, argp);
};
