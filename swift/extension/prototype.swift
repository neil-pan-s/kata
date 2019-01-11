
/*
扩展 就是为一个已有的类、结构体、枚举类型或者协议类型添加新功能。这包括在没有权限获取原始源代码的情况下扩展类型的能力（即 逆向建模 ）。扩展和 Objective-C 中的分类类似。（与 Objective-C 不同的是，Swift 的扩展没有名字。）

Swift 中的扩展可以：

添加计算型属性和计算型类型属性
定义实例方法和类型方法
提供新的构造器
定义下标
定义和使用新的嵌套类型
使一个已有类型符合某个协议
在 Swift 中，你甚至可以对协议进行扩展，提供协议要求的实现，或者添加额外的功能，从而可以让符合协议的类型拥有这些功能。你可以从协议扩展获取更多的细节。

注意

扩展可以为一个类型添加新的功能，但是不能重写已有的功能。

扩展语法
使用关键字 extension 来声明扩展：

extension SomeType {
    // 为 SomeType 添加的新功能写到这里
}
可以通过扩展来扩展一个已有类型，使其采纳一个或多个协议。在这种情况下，无论是类还是结构体，协议名字的书写方式完全一样：

extension SomeType: SomeProtocol, AnotherProctocol {
    // 协议实现写到这里
}
通过这种方式添加协议一致性的详细描述请参阅利用扩展添加协议一致性。

注意

如果你通过扩展为一个已有类型添加新功能，那么新功能对该类型的所有已有实例都是可用的，即使它们是在这个扩展定义之前创建的。
*/

/*
计算型属性
扩展可以为已有类型添加计算型实例属性和计算型类型属性。下面的例子为 Swift 的内建 Double 类型添加了五个计算型实例属性，从而提供与距离单位协作的基本支持：

扩展可以添加新的计算型属性，但是不可以添加存储型属性，也不可以为已有属性添加属性观察器。

*/

extension Double {
    var km: Double { return self * 1_000.0 }
    var m : Double { return self }
    var cm: Double { return self / 100.0 }
    var mm: Double { return self / 1_000.0 }
    var ft: Double { return self / 3.28084 }
}
let oneInch = 25.4.mm
print("One inch is \(oneInch) meters")
// 打印 “One inch is 0.0254 meters”
let threeFeet = 3.ft
print("Three feet is \(threeFeet) meters")
// 打印 “Three feet is 0.914399970739201 meters”

/*
构造器
扩展可以为已有类型添加新的构造器。这可以让你扩展其它类型，将你自己的定制类型作为其构造器参数，或者提供该类型的原始实现中未提供的额外初始化选项。

扩展能为类添加新的便利构造器，但是它们不能为类添加新的指定构造器或析构器。指定构造器和析构器必须总是由原始的类实现来提供。
*/

struct Size {
    var width = 0.0, height = 0.0
}
struct Point {
    var x = 0.0, y = 0.0
}
struct Rect {
    var origin = Point()
    var size = Size()
}

let defaultRect = Rect()
let memberwiseRect = Rect(origin: Point(x: 2.0, y: 2.0),
    size: Size(width: 5.0, height: 5.0))

extension Rect {
    init(center: Point, size: Size) {
        let originX = center.x - (size.width / 2)
        let originY = center.y - (size.height / 2)
        self.init(origin: Point(x: originX, y: originY), size: size)
    }
}

let centerRect = Rect(center: Point(x: 4.0, y: 4.0),
    size: Size(width: 3.0, height: 3.0))
// centerRect 的原点是 (2.5, 2.5)，大小是 (3.0, 3.0)

/*
方法
扩展可以为已有类型添加新的实例方法和类型方法。下面的例子为 Int 类型添加了一个名为 repetitions 的实例方法：
*/

extension Int {
    func repetitions(task: () -> Void) {
        for _ in 0..<self {
            task()
        }
    }
}

// 定义该扩展之后，你就可以对任意整数调用 repetitions(task:) 方法，将闭包中的任务执行整数对应的次数：

3.repetitions({
    print("Hello!")
})
// Hello!
// Hello!
// Hello!

/*
可变实例方法
通过扩展添加的实例方法也可以修改该实例本身。结构体和枚举类型中修改 self 或其属性的方法必须将该实例方法标注为 mutating，正如来自原始实现的可变方法一样。

下面的例子为 Swift 的 Int 类型添加了一个名为 square 的可变方法，用于计算原始值的平方值：
*/

extension Int {
    mutating func square() {
        self = self * self
    }
}
var someInt = 3
someInt.square()
// someInt 的值现在是 9

/*
下标
扩展可以为已有类型添加新下标。这个例子为 Swift 内建类型 Int 添加了一个整型下标。该下标 [n] 返回十进制数字从右向左数的第 n 个数字：

123456789[0] 返回 9
123456789[1] 返回 8
……以此类推。
*/

extension Int {
    subscript(digitIndex: Int) -> Int {
        var decimalBase = 1
        for _ in 0..<digitIndex {
            decimalBase *= 10
        }
        return (self / decimalBase) % 10
    }
}
746381295[0]
// 返回 5
746381295[1]
// 返回 9
746381295[2]
// 返回 2
746381295[8]
// 返回 7

