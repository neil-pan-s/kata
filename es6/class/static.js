/**
 * 如果在一个方法前，加上static关键字，就表示该方法不会被实例继承，而是直接通过类来调用，这就称为“静态方法”。
 */

//case 1 静态方法
class Foo {
    static classMethod() {
        return 'hello';
    }
}

Foo.classMethod() // 'hello'

var foo = new Foo();
foo.classMethod();
// TypeError: foo.classMethod is not a function

//case 2 父类的静态方法，可以被子类继承。
class Foo2 {
    static classMethod() {
        return 'hello';
    }
}

class Bar2 extends Foo2 {}

Bar2.classMethod() // 'hello'

//静态方法也是可以从super对象上调用的。
class Foo3 {
    static classMethod() {
        return 'hello';
    }
}

class Bar3 extends Foo3 {
    static classMethod() {
        return super.classMethod() + ', too';
    }
}

Bar3.classMethod() // "hello, too"

//case 3 静态属性
//ES6 明确规定，Class 内部只有静态方法，没有静态属性。
//静态属性指的是 Class 本身的属性，即Class.propName，而不是定义在实例对象（this）上的属性。
class Foo {}

Foo.prop = 1;
Foo.prop // 1


//case 4 实例属性
class Foo {
    constructor(props) {
        this.state = {
            count: 0
        };
    }
}