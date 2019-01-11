var handler = {
    get: function(target, name) {
        console.log("handler get call");

        if (name === 'prototype') {
            return Object.prototype;
        }
        return 'Hello, ' + name;
    },

    apply: function(target, thisBinding, args) {
        console.log("handler apply call");
        return args[0];
    },

    construct: function(target, args) {
        console.log("handler construct call");
        return { value: args[1] };
    }
};

var fproxy = new Proxy(function(x, y) {
    return x + y;
}, handler);

//调用Proxy apply方法
fproxy(1, 2) // 1

//调用Proxy construct方法
new fproxy(1, 2) // {value: 2}
fproxy.prototype === Object.prototype // true

//调用Proxy get方法
fproxy.foo // "Hello, foo"