//私有方法定义

//模块化后不导出此部分定义
const bar = Symbol('bar');
const foo = Symbol('foo');
const name = Symbol('name');

/*export default*/
class myClass {

    constructor() {
        //私有属性
        this[name] = "I'm priavte property";
    }

    // 公有方法
    foo(baz) {
        this[bar](baz);
    }

    // 私有方法
    [bar](baz) {
        return this[foo] = baz;
    }

    // ...
};