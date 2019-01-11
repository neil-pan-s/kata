
/*
类实例之间的循环强引用
在上面的例子中，ARC 会跟踪你所新创建的 Person 实例的引用数量，并且会在 Person 实例不再被需要时销毁它。

然而，我们可能会写出一个类实例的强引用数永远不能变成 0 的代码。如果两个类实例互相持有对方的强引用，因而每个实例都让对方一直存在，就是这种情况。这就是所谓的循环强引用。

你可以通过定义类之间的关系为弱引用或无主引用，以替代强引用，从而解决循环强引用的问题。

弱引用和无主引用允许循环引用中的一个实例引用而另外一个实例不保持强引用。这样实例能够互相引用而不产生循环强引用。
*/

class Person {
    let name: String
    init(name: String) { self.name = name }
    var apartment: Apartment?
    deinit { print("\(name) is being deinitialized") }
}

class Apartment {
    let unit: String
    init(unit: String) { self.unit = unit }
    var tenant: Person?
    deinit { print("Apartment \(unit) is being deinitialized") }
}

var john: Person?
var unit4A: Apartment?

john = Person(name: "John Appleseed")
unit4A = Apartment(unit: "4A")

john!.apartment = unit4A
unit4A!.tenant = john

john = nil
unit4A = nil

// 注意，当你把这两个变量设为 nil 时，没有任何一个析构函数被调用。循环强引用会一直阻止 Person 和 Apartment 类实例的销毁，这就在你的应用程序中造成了内存泄漏。


