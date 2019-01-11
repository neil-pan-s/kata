
/*
枚举语法
使用 enum 关键词来创建枚举并且把它们的整个定义放在一对大括号内：
*/
enum SomeEnumeration {
    // 枚举定义放在这里
}
// 下面是用枚举表示指南针四个方向的例子：

enum CompassPoint {
    case north
    case south
    case east
    case west
}

// 多个成员值可以出现在同一行上，用逗号隔开：

enum Planet {
    case mercury, venus, earth, mars, jupiter, saturn, uranus, neptune
}

var directionToHead = CompassPoint.west
// directionToHead 的类型可以在它被 CompassPoint 的某个值初始化时推断出来。一旦 directionToHead 被声明为 CompassPoint 类型，你可以使用更简短的点语法将其设置为另一个 CompassPoint 的值：

directionToHead = .east
// 当 directionToHead 的类型已知时，再次为其赋值可以省略枚举类型名。

// 使用 Switch 语句匹配枚举值

directionToHead = .south
switch directionToHead {
    case .north:
        print("Lots of planets have a north")
    case .south:
        print("Watch out for penguins")
    case .east:
        print("Where the sun rises")
    case .west:
        print("Where the skies are blue")
}
// 打印 "Watch out for penguins”

/*
关联值
上一小节的例子演示了如何定义和分类枚举的成员。你可以为 Planet.earth 设置一个常量或者变量，并在赋值之后查看这个值。然而，有时候能够把其他类型的关联值和成员值一起存储起来会很有用。这能让你连同成员值一起存储额外的自定义信息，并且你每次在代码中使用该枚举成员时，还可以修改这个关联值。
*/

// 在 Swift 中，使用如下方式定义表示两种商品条形码的枚举：

enum Barcode {
    case upc(Int, Int, Int, Int)
    case qrCode(String)
}

var productBarcode = Barcode.upc(8, 85909, 51226, 3)
productBarcode = .qrCode("ABCDEFGHIJKLMNOP")

switch productBarcode {
case .upc(let numberSystem, let manufacturer, let product, let check):
    print("UPC: \(numberSystem), \(manufacturer), \(product), \(check).")
case .qrCode(let productCode):
    print("QR code: \(productCode).")
}
// 打印 "QR code: ABCDEFGHIJKLMNOP."

// 如果一个枚举成员的所有关联值都被提取为常量，或者都被提取为变量，为了简洁，你可以只在成员名称前标注一个 let 或者 var：

switch productBarcode {
case let .upc(numberSystem, manufacturer, product, check):
    print("UPC: \(numberSystem), \(manufacturer), \(product), \(check).")
case let .qrCode(productCode):
    print("QR code: \(productCode).")
}
// 输出 "QR code: ABCDEFGHIJKLMNOP."

/*
原始值
在关联值小节的条形码例子中，演示了如何声明存储不同类型关联值的枚举成员。作为关联值的替代选择，枚举成员可以被默认值（称为原始值）预填充，这些原始值的类型必须相同。

原始值的隐式赋值
在使用原始值为整数或者字符串类型的枚举时，不需要显式地为每一个枚举成员设置原始值，Swift 将会自动为你赋值。
*/ 

// 例如，当使用整数作为原始值时，隐式赋值的值依次递增 1。如果第一个枚举成员没有设置原始值，其原始值将为 0。

// 下面的枚举是对之前 Planet 这个枚举的一个细化，利用整型的原始值来表示每个行星在太阳系中的顺序：

enum Planet1: Int {
    case mercury = 1, venus, earth, mars, jupiter, saturn, uranus, neptune
}

// 当使用字符串作为枚举类型的原始值时，每个枚举成员的隐式原始值为该枚举成员的名称。

// 下面的例子是 CompassPoint 枚举的细化，使用字符串类型的原始值来表示各个方向的名称：

enum CompassPoint1: String {
    case north, south, east, west
}

// 使用枚举成员的 rawValue 属性可以访问该枚举成员的原始值：

let earthsOrder = Planet1.earth.rawValue
// earthsOrder 值为 3

let sunsetDirection = CompassPoint1.west.rawValue
// sunsetDirection 值为 "west"

/*
使用原始值初始化枚举实例
如果在定义枚举类型的时候使用了原始值，那么将会自动获得一个初始化方法，这个方法接收一个叫做 rawValue 的参数，参数类型即为原始值类型，返回值则是枚举成员或 nil。你可以使用这个初始化方法来创建一个新的枚举实例。
*/

// 这个例子利用原始值 7 创建了枚举成员 uranus：

let possiblePlanet = Planet1(rawValue: 7)
// possiblePlanet 类型为 Planet? 值为 Planet.uranus

/*
递归枚举
递归枚举是一种枚举类型，它有一个或多个枚举成员使用该枚举类型的实例作为关联值。使用递归枚举时，编译器会插入一个间接层。你可以在枚举成员前加上 indirect 来表示该成员可递归。

例如，下面的例子中，枚举类型存储了简单的算术表达式：
*/

enum ArithmeticExpression {
    case number(Int)
    indirect case addition(ArithmeticExpression, ArithmeticExpression)
    indirect case multiplication(ArithmeticExpression, ArithmeticExpression)
}

// 你也可以在枚举类型开头加上 indirect 关键字来表明它的所有成员都是可递归的：

/*
indirect enum ArithmeticExpression {
    case number(Int)
    case addition(ArithmeticExpression, ArithmeticExpression)
    case multiplication(ArithmeticExpression, ArithmeticExpression)
}
*/
