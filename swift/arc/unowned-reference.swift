
/*
无主引用
和弱引用类似，无主引用不会牢牢保持住引用的实例。和弱引用不同的是，无主引用在其他实例有相同或者更长的生命周期时使用。你可以在声明属性或者变量时，在前面加上关键字 unowned 表示这是一个无主引用。

无主引用通常都被期望拥有值。不过 ARC 无法在实例被销毁后将无主引用设为 nil，因为非可选类型的变量不允许被赋值为 nil。

重点

使用无主引用，你必须确保引用始终指向一个未销毁的实例。

如果你试图在实例被销毁后，访问该实例的无主引用，会触发运行时错误。
*/

class Customer {
    let name: String
    var card: CreditCard?
    init(name: String) {
        self.name = name
    }
    deinit { print("\(name) is being deinitialized") }
}

class CreditCard {
    let number: UInt64
    unowned let customer: Customer
    init(number: UInt64, customer: Customer) {
        self.number = number
        self.customer = customer
    }
    deinit { print("Card #\(number) is being deinitialized") }
}


var john: Customer?
john = Customer(name: "John Appleseed")
john!.card = CreditCard(number: 1234_5678_9012_3456, customer: john!)
john = nil
// 打印 "John Appleseed is being deinitialized"
// 打印 "Card #1234567890123456 is being deinitialized"

// 由于 customer 的无主引用，当你断开 john 变量持有的强引用时，再也没有指向 Customer 实例的强引用了
// 由于再也没有指向 Customer 实例的强引用，该实例被销毁了。其后，再也没有指向 CreditCard 实例的强引用，该实例也随之被销毁了




