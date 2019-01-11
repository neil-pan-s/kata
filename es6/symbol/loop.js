//Symbol 作为属性名，该属性不会出现在for...in、for...of循环中，也不会被Object.keys()、Object.getOwnPropertyNames()、JSON.stringify()返回。
//它也不是私有属性，有一个Object.getOwnPropertySymbols方法，可以获取指定对象的所有 Symbol 属性名。

const COLOR_RED = Symbol();
const COLOR_GREEN = Symbol();

var obj = {
    [COLOR_RED]: 'red',
    [COLOR_GREEN]: 'green',
    COLOR_BLACK: 'black'
};

for (var x in obj) {
    console.log(x);
}