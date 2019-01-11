//为变量指定一个变量ID

//case 1
let x = Symbol();
console.log(x);

//case 2 指定描述的Symbol
let y = Symbol("foo");

//case 3 Symbol 对象参数
const obj = {
    toString() {
        return 'abc';
    }
};
const sym = Symbol(obj);
console.log(sym) // Symbol(abc)