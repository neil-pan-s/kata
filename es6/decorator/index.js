/**
 * ES-7 内容 Chrome & Node unsupport 需要Babel转码
 *
 *   @decorator
 *   class A {}
 * 
 *   等同于
 *   
 *   class A {}
 *   A = decorator(A) || A;
 * 
 *  扩展修饰符:   @readonly   @nonenumerable  ...
 */

//case 1 
function testable(isTestable = true) {
    return function(target) {
        target.isTestable = isTestable;
    }
}

@testable
class MyTestableClass {}
MyTestableClass.isTestable // true

@testable(false)
class MyClass {}
MyClass.isTestable // false