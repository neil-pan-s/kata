
/*
self 属性
类型的每一个实例都有一个隐含属性叫做 self，self 完全等同于该实例本身。你可以在一个实例的实例方法中使用这个隐含的 self 属性来引用当前实例。


func increment() {
    self.count += 1
}
实际上，你不必在你的代码里面经常写 self。
*/

// 下面的例子中，self 消除方法参数 x 和实例属性 x 之间的歧义：

struct Point {
    var x = 0.0, y = 0.0
    func isToTheRightOfX(_ x: Double) -> Bool {
        return self.x > x
    }
}
let somePoint = Point(x: 4.0, y: 5.0)
if somePoint.isToTheRightOfX(1.0) {
    print("This point is to the right of the line where x == 1.0")
}
// 打印 "This point is to the right of the line where x == 1.0"

/*
在可变方法中给 self 赋值
可变方法能够赋给隐含属性 self 一个全新的实例。上面 Point 的例子可以用下面的方式改写：
*/

struct Point {
    var x = 0.0, y = 0.0
    mutating func moveBy(x deltaX: Double, y deltaY: Double) {
        self = Point(x: x + deltaX, y: y + deltaY)
    }
}
// 新版的可变方法 moveBy(x:y:) 创建了一个新的结构体实例，它的 x 和 y 的值都被设定为目标值。调用这个版本的方法和调用上个版本的最终结果是一样的。

// 枚举的可变方法可以把 self 设置为同一枚举类型中不同的成员：

enum TriStateSwitch {
    case Off, Low, High
    mutating func next() {
        switch self {
        case .Off:
            self = .Low
        case .Low:
            self = .High
        case .High:
            self = .Off
        }
    }
}
var ovenLight = TriStateSwitch.Low
ovenLight.next()
// ovenLight 现在等于 .High
ovenLight.next()
// ovenLight 现在等于 .Off
// 上面的例子中定义了一个三态开关的枚举。每次调用 next() 方法时，开关在不同的电源状态（Off，Low，High）之间循环切换。
