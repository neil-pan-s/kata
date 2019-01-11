
//对象的每一个属性都有一个描述对象

//case 1
let obj = {name : 'fish'};
var des = Object.getOwnPropertyDescriptor(obj, 'name');
console.log(des);

//case 2
var o, d;

o = { get foo() { return 17; } };
d = Object.getOwnPropertyDescriptor(o, "foo");
//d is {configurable: true, enumerable: true, get: /*访问器函数*/, set: undefined }

o = { bar: 42 };
d = Object.getOwnPropertyDescriptor(o, "bar");
// d is { configurable: true, enumerable: true, value: 42, writable: true }

//case 3 
o = {};
Object.defineProperty(o, "baz", { value: 8675309, writable: false, enumerable: false });
d = Object.getOwnPropertyDescriptor(o, "baz");
// d is {value: 8675309, writable: false, enumerable: false, configurable: false }
