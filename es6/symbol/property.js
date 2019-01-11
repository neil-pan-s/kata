//case 1 Symbol property

var mySymbol = Symbol();

// 第一种写法
var a = {};
a[mySymbol] = 'Hello!';
//a.mySymbol  // throw error

// 第二种写法
var a = {
    [mySymbol]: 'Hello!'
};
console.log(a[mySymbol]);

//case 2 用作函数名
var a = {
    [mySymbol]() {
        console.log('Hello!');
    }
};
console.log(a[mySymbol]());

//case 3 Symbol.for 根据foo 查询是否存在 存在则返回同一Symbol
let y = Symbol("foo");

let z1 = Symbol.for("foo");
let z2 = Symbol.for("foo");

console.log(y.toString());
console.log(y, z1, y == z1, z1 === z2);

var o = {
    [y]: 'hello',
    [z1]: 'hi',
    [z2]: 'ha'
};

console.log(o, o[y], o[z1], o[z2]);