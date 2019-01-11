//case 1
class Point {
    //构造器方法
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }

    //扩展方法
    toString() {
        return '(' + this.x + ', ' + this.y + ')';
    }
}

var p = new Point(1, 2);
p.constructor === Point.prototype.constructor //true

//case 2 
class Point {
    toString() {
        // ...
    }

    toValue() {
        // ...
    }
}

// 等同于

Point.prototype = {
    //一个类必须有constructor方法，如果没有显式定义，一个空的constructor方法会被默认添加。
    constructor() {},
    toString() {},
    toValue() {},
};

Point === Point.prototype.constructor // true

//case 3 类的内部所有定义的方法，都是不可枚举的（non-enumerable）
Object.keys(Point.prototype);
// []
Object.getOwnPropertyNames(Point.prototype);
// ["constructor","toString"]

//case 4 不存在变量提升
new Foo(); // ReferenceError
class Foo {}