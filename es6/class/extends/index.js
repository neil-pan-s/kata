//case 1 子类必须在constructor方法中调用super方法，否则新建实例时会报错。
//这是因为子类没有自己的this对象，而是继承父类的this对象，然后对其进行加工。
class Point {}

class ColorPoint extends Point {}

// 等同于
class ColorPoint extends Point {
    constructor(...args) {
        //必须第一步调用super 否则后续通过this创建属性会出错
        super(...args);
    }
}

let cp = new ColorPoint(25, 8, 'green');
cp instanceof ColorPoint // true
cp instanceof Point // true


//case 2 判断一个类是否继承了另一个类。
Object.getPrototypeOf(ColorPoint) === Point;
// true

//case 3 super 关键字
class A {
    constructor() {
        this.p = 2;
    }
}

class B extends A {
    constructor() {
        //ES6 规定，通过super调用父类的方法时，super会绑定子类的this。
        //等同于 A.prototype.constructor.call(this)
        //所以 this.p 实际上添加在子类实例上 
        super();
    }

    get m() {
        //super在普通方法之中，指向A.prototype 
        return super.p; // undefined, A.prototype中无p属性
        //return this.p; //2
    }
}

let b = new B(); //B {p: 2}p: 2m: (...)__proto__: A
b.m // undefined

//case 4 super static 
//super在静态方法之中指向父类，在普通方法之中指向父类的原型对象。
//所以静态方法中无法调用到原型方法，原型方法中无法调用到静态方法。
class Parent {
    static myMethod(msg) {
        console.log('static', msg);
    }

    myMethod(msg) {
        console.log('instance', msg);
    }
}

class Child extends Parent {
    static myMethod(msg) {
        super.myMethod(msg);
    }

    myMethod(msg) {
        super.myMethod(msg);
    }
}

Child.myMethod(1); // static 1

var child = new Child();
child.myMethod(2); // instance 2