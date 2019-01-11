
/*
属性的访问冲突
如结构体，元组和枚举的类型都是由多个独立的值组成的，例如结构体的属性或元组的元素。因为它们都是值类型，修改值的任何一部分都是对于整个值的修改，意味着其中一个属性的读或写访问都需要访问整一个值。例如，元组元素的写访问重叠会产生冲突：

var playerInformation = (health: 10, energy: 20)
balance(&playerInformation.health, &playerInformation.energy)
// 错误：playerInformation 的属性访问冲突
上面的例子里，传入同一元组的元素对 balance(_:_:) 进行调用，产生了冲突，因为 playerInformation 的访问产生了写访问重叠。playerInformation.health 和 playerInformation.energy 都被作为参数传入，意味着 balance(_:_:) 需要在函数调用期间对它们发起写访问。任何情况下，对于元组元素的写访问都需要对整个元组发起写访问。这意味着对于 playerInfomation 发起的两个写访问重叠了，造成冲突。

下面的代码展示了一样的错误，对于一个存储在全局变量里的结构体属性的写访问重叠了。

var holly = Player(name: "Holly", health: 10, energy: 10)
balance(&holly.health, &holly.energy)  // 错误
在实践中，大多数对于结构体属性的访问都会安全的重叠。例如，将上面例子里的变量 holly 改为本地变量而非全局变量，编译器就会可以保证这个重叠访问时安全的：

func someFunction() {
    var oscar = Player(name: "Oscar", health: 10, energy: 10)
    balance(&oscar.health, &oscar.energy)  // 正常
}
上面的例子里，oscar 的 health 和 energy 都作为 in-out 参数传入了 balance(_:_:) 里。编译器可以保证内存安全，因为两个存储属性任何情况下都不会相互影响。

限制结构体属性的重叠访问对于内存安全并不总是必要的。内存安全是必要的，但访问独占权的要求比内存安全还要更严格 —— 意味着即使有些代码违反了访问独占权的原则，也是内存安全的。如果编译器可以保证这种非专属的访问是安全的，那 Swift 就会允许这种内存安全的行为。特别是当你遵循下面的原则时，它可以保证结构体属性的重叠访问是安全的：

你访问的是实例的存储属性，而不是计算属性或类的属性
结构体是本地变量的值，而非全局变量
结构体要么没有被闭包捕获，要么只被非逃逸闭包捕获了
如果编译器无法保证访问的安全性，它就不会允许访问。
*/

