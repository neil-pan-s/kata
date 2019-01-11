/**
 * new是从构造函数生成实例的命令。ES6 为new命令引入了一个new.target属性，该属性一般用在在构造函数之中，
 * 返回new命令作用于的那个构造函数。
 * 如果构造函数不是通过new命令调用的，new.target会返回undefined
 */

//case 1 判断是否通过new 命令生成
function Person(name) {
    //Class 内部调用new.target，返回当前 Class。
    if (new.target === Person) {
        this.name = name;
    } else {
        throw new Error('必须使用 new 生成实例');
    }
}

var person = new Person('张三'); // 正确
var notAPerson = Person.call({}, '张三'); // 报错

//case 2 子类继承父类时，new.target会返回子类
class Rectangle {
    constructor(length, width) {
        console.log(new.target === Rectangle);
        // ...
    }
}

class Square extends Rectangle {
    constructor(length) {
        super(length, length);
    }
}
var obj = new Square(3); // 输出 false

//case 3 虚函数类 不能独立使用、必须继承后才能使用的类
class Shape {
    constructor() {
        if (new.target === Shape) {
            throw new Error('本类不能实例化');
        }
    }
}

class Rectangle extends Shape {
    constructor(length, width) {
        super();
        // ...
    }
}

var x = new Shape(); // 报错
var y = new Rectangle(3, 4); // 正确