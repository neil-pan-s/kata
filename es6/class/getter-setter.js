class MyClass {
    constructor() {
        // ...
    }
    get prop() {
        return 'getter';
    }
    set prop(value) {
        console.log('setter: ' + value);
    }
}

let inst = new MyClass();

inst.prop = 123;
// setter: 123

inst.prop;
// 'getter'

//存值函数和取值函数是设置在属性的 Descriptor 对象上的。
var descriptor = Object.getOwnPropertyDescriptor(
    MyClass.prototype, "prop"
);

"get" in descriptor; // true
"set" in descriptor; // true