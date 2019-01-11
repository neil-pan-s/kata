
/*
类和结构体有着类似的定义方式。我们通过关键字 class 和 struct 来分别表示类和结构体，并在一对大括号中定义它们的具体内容：
*/

class SomeClass {
    // 在这里定义类
}
struct SomeStructure {
    // 在这里定义结构体
}

// 以下是定义结构体和定义类的示例：

struct Resolution {
    var width = 0
    var height = 0
}
class VideoMode {
    var resolution = Resolution()
    var interlaced = false
    var frameRate = 0.0
    var name: String?
}

// 生成结构体和类实例的语法非常相似：

let someResolution = Resolution()
let someVideoMode = VideoMode()

/*
结构体和类都使用构造器语法来生成新的实例。构造器语法的最简单形式是在结构体或者类的类型名称后跟随一对空括号，如 Resolution() 或 VideoMode()。
*/

/*
属性访问
通过使用点语法，你可以访问实例的属性。
*/

print("The width of someResolution is \(someResolution.width)")
// 打印 "The width of someResolution is 0"

// 你也可以使用点语法为变量属性赋值：

someVideoMode.resolution.width = 1280
print("The width of someVideoMode is now \(someVideoMode.resolution.width)")
// 打印 "The width of someVideoMode is now 1280"

/*
结构体类型的成员逐一构造器
所有结构体都有一个自动生成的成员逐一构造器，用于初始化新结构体实例中成员的属性。新实例中各个属性的初始值可以通过属性的名称传递到成员逐一构造器之中,
与结构体不同，类实例没有默认的成员逐一构造器。
*/

let vga = Resolution(width: 640, height: 480)

/*
结构体和枚举是值类型
值类型被赋予给一个变量、常量或者被传递给一个函数的时候，其值会被拷贝。

在之前的章节中，我们已经大量使用了值类型。实际上，在 Swift 中，所有的基本类型：整数（Integers）、浮点数（floating-point numbers）、布尔值（Booleans）、字符串（strings)、数组（arrays）和字典（dictionaries），都是值类型，并且在底层都是以结构体的形式所实现。

在 Swift 中，所有的结构体和枚举类型都是值类型。这意味着它们的实例，以及实例中所包含的任何值类型属性，在代码中传递的时候都会被复制。
*/

// 请看下面这个示例，其使用了前一个示例中的 Resolution 结构体：

let hd = Resolution(width: 1920, height: 1080)
var cinema = hd
cinema.width = 2048
// 这里，将会显示 cinema 的 width 属性确已改为了 2048：

print("cinema is now  \(cinema.width) pixels wide")
// 打印 "cinema is now 2048 pixels wide"
// 然而，初始的 hd 实例中 width 属性还是 1920：

print("hd is still \(hd.width) pixels wide")
// 打印 "hd is still 1920 pixels wide"

// 枚举也遵循相同的行为准则：

enum CompassPoint {
    case North, South, East, West
}
var currentDirection = CompassPoint.West
let rememberedDirection = currentDirection
currentDirection = .East
if rememberedDirection == .West {
    print("The remembered direction is still .West")
}
// 打印 "The remembered direction is still .West"

/*
类是引用类型
与值类型不同，引用类型在被赋予到一个变量、常量或者被传递到一个函数时，其值不会被拷贝。因此，引用的是已存在的实例本身而不是其拷贝。
*/

/*
恒等运算符
因为类是引用类型，有可能有多个常量和变量在幕后同时引用同一个类实例。（对于结构体和枚举来说，这并不成立。因为它们作为值类型，在被赋予到常量、变量或者传递到函数时，其值总是会被拷贝。）

如果能够判定两个常量或者变量是否引用同一个类实例将会很有帮助。为了达到这个目的，Swift 内建了两个恒等运算符：

等价于（===）
不等价于（!==）
*/

/*
按照通用的准则，当符合一条或多条以下条件时，请考虑构建结构体：

该数据结构的主要目的是用来封装少量相关简单数据值。
有理由预计该数据结构的实例在被赋值或传递时，封装的数据将会被拷贝而不是被引用。
该数据结构中储存的值类型属性，也应该被拷贝，而不是被引用。
该数据结构不需要去继承另一个既有类型的属性或者行为。
举例来说，以下情境中适合使用结构体：

几何形状的大小，封装一个 width 属性和 height 属性，两者均为 Double 类型。
一定范围内的路径，封装一个 start 属性和 length 属性，两者均为 Int 类型。
三维坐标系内一点，封装 x，y 和 z 属性，三者均为 Double 类型。
在所有其它案例中，定义一个类，生成一个它的实例，并通过引用来管理和传递。实际中，这意味着绝大部分的自定义数据构造都应该是类，而非结构体。
*/
