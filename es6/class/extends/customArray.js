//extends关键字不仅可以用来继承类，还可以用来继承原生的构造函数。因此可以在原生数据结构的基础上，定义自己的数据结构
class CustomArray extends Array {
    constructor(...args) {
        super(...args);
    }
    push(...args) {
        console.log("CustomArray push");
        return super.push(...args);
    }
    pop(...args) {
        console.log("CustomArray pop");
        return super.pop(...args);
    }
}

var x = new CustomArray();

x.push(1);
x.pop();