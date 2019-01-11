
/*
构造过程是使用类、结构体或枚举类型的实例之前的准备过程。在新实例可用前必须执行这个过程，具体操作包括设置实例中每个存储型属性的初始值和执行其他必须的设置或初始化工作。

通过定义构造器来实现构造过程，就像用来创建特定类型新实例的特殊方法。与 Objective-C 中的构造器不同，Swift 的构造器无需返回值，它们的主要任务是保证新实例在第一次使用前完成正确的初始化。

类的实例也可以通过定义析构器在实例释放之前执行特定的清除工作。想了解更多关于析构器的内容，请参考析构过程。


存储属性的初始赋值
类和结构体在创建实例时，必须为所有存储型属性设置合适的初始值。存储型属性的值不能处于一个未知的状态。

你可以在构造器中为存储型属性赋初值，也可以在定义属性时为其设置默认值。以下小节将详细介绍这两种方法。

注意

当你为存储型属性设置默认值或者在构造器中为其赋值时，它们的值是被直接设置的，不会触发任何属性观察者。


构造器
构造器在创建某个特定类型的新实例时被调用。它的最简形式类似于一个不带任何参数的实例方法，以关键字 init 命名：

init() {
    // 在此处执行构造过程
}
*/

/*
构造参数
自定义构造过程时，可以在定义中提供构造参数，指定参数值的类型和名字。构造参数的功能和语法跟函数和方法的参数相同。
*/

// 下面例子中定义了一个包含摄氏度温度的结构体 Celsius。它定义了两个不同的构造器：init(fromFahrenheit:) 和 init(fromKelvin:)，二者分别通过接受不同温标下的温度值来创建新的实例：

struct Celsius {
    var temperatureInCelsius: Double
    init(fromFahrenheit fahrenheit: Double) {
        temperatureInCelsius = (fahrenheit - 32.0) / 1.8
    }
    init(fromKelvin kelvin: Double) {
        temperatureInCelsius = kelvin - 273.15
    }
}

let boilingPointOfWater = Celsius(fromFahrenheit: 212.0)
// boilingPointOfWater.temperatureInCelsius 是 100.0
let freezingPointOfWater = Celsius(fromKelvin: 273.15)
// freezingPointOfWater.temperatureInCelsius 是 0.0

/*
不带参数标签的构造器参数
如果你不希望为构造器的某个参数提供参数标签，你可以使用下划线（_）来显式描述它的外部名，以此重写上面所说的默认行为。
*/

// 下面是之前 Celsius 例子的扩展，跟之前相比添加了一个带有 Double 类型参数的构造器，其外部名用 _ 代替：

struct Celsius {
    var temperatureInCelsius: Double
    init(fromFahrenheit fahrenheit: Double) {
        temperatureInCelsius = (fahrenheit - 32.0) / 1.8
    }
    init(fromKelvin kelvin: Double) {
        temperatureInCelsius = kelvin - 273.15
    }
    init(_ celsius: Double){
        temperatureInCelsius = celsius
    }
}

let bodyTemperature = Celsius(37.0)
// bodyTemperature.temperatureInCelsius 为 37.0

/*
构造过程中常量属性的赋值
你可以在构造过程中的任意时间点给常量属性指定一个值，只要在构造过程结束时是一个确定的值。一旦常量属性被赋值，它将永远不可更改。

注意

对于类的实例来说，它的常量属性只能在定义它的类的构造过程中修改；不能在子类中修改。

可选属性类型
如果你定制的类型包含一个逻辑上允许取值为空的存储型属性——无论是因为它无法在初始化时赋值，还是因为它在之后某个时间点可以赋值为空——你都需要将它定义为 可选类型。可选类型的属性将自动初始化为 nil，表示这个属性是有意在初始化时设置为空的。
*/

/*
值类型的构造器代理
构造器可以通过调用其它构造器来完成实例的部分构造过程。这一过程称为构造器代理，它能避免多个构造器间的代码重复。
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
    init() {}

    init(origin: Point, size: Size) {
        self.origin = origin
        self.size = size
    }

    init(center: Point, size: Size) {
        let originX = center.x - (size.width / 2)
        let originY = center.y - (size.height / 2)
        self.init(origin: Point(x: originX, y: originY), size: size)
    }
}

/*
指定构造器和便利构造器的语法
类的指定构造器的写法跟值类型简单构造器一样：

init(parameters) {
    statements
}
便利构造器也采用相同样式的写法，但需要在 init 关键字之前放置 convenience 关键字，并使用空格将它们俩分开：

convenience init(parameters) {
    statements
}

类的构造器代理规则
为了简化指定构造器和便利构造器之间的调用关系，Swift 采用以下三条规则来限制构造器之间的代理调用：

规则 1
    指定构造器必须调用其直接父类的的指定构造器。

规则 2
    便利构造器必须调用同类中定义的其它构造器。

规则 3
    便利构造器最后必须调用指定构造器。

一个更方便记忆的方法是：

指定构造器必须总是向上代理
便利构造器必须总是横向代理
*/

/*
构造器的继承和重写
跟 Objective-C 中的子类不同，Swift 中的子类默认情况下不会继承父类的构造器。Swift 的这种机制可以防止一个父类的简单构造器被一个更精细的子类继承，并被错误地用来创建子类的实例。
*/

// 下面例子中定义了一个 Vehicle 的子类 Bicycle：

class Bicycle: Vehicle {
    override init() {
        super.init()
        numberOfWheels = 2
    }
}

/*
构造器的自动继承
如上所述，子类在默认情况下不会继承父类的构造器。但是如果满足特定条件，父类构造器是可以被自动继承的。事实上，这意味着对于许多常见场景你不必重写父类的构造器，并且可以在安全的情况下以最小的代价继承父类的构造器。

假设你为子类中引入的所有新属性都提供了默认值，以下 2 个规则适用：

规则 1
    如果子类没有定义任何指定构造器，它将自动继承父类所有的指定构造器。

规则 2
    如果子类提供了所有父类指定构造器的实现——无论是通过规则 1 继承过来的，还是提供了自定义实现——它将自动继承父类所有的便利构造器。

即使你在子类中添加了更多的便利构造器，这两条规则仍然适用。

注意

对于规则 2，子类可以将父类的指定构造器实现为便利构造器。
*/

/*
可失败构造器
如果一个类、结构体或枚举类型的对象，在构造过程中有可能失败，则为其定义一个可失败构造器是很有用的。这里所指的“失败” 指的是，如给构造器传入无效的参数值，或缺少某种所需的外部资源，又或是不满足某种必要的条件等。

为了妥善处理这种构造过程中可能会失败的情况。你可以在一个类，结构体或是枚举类型的定义中，添加一个或多个可失败构造器。其语法为在 init 关键字后面添加问号（init?）。

注意

可失败构造器的参数名和参数类型，不能与其它非可失败构造器的参数名，及其参数类型相同。

可失败构造器会创建一个类型为自身类型的可选类型的对象。你通过 return nil 语句来表明可失败构造器在何种情况下应该 “失败”。

注意

严格来说，构造器都不支持返回值。因为构造器本身的作用，只是为了确保对象能被正确构造。因此你只是用 return nil 表明可失败构造器构造失败，而不要用关键字 return 来表明构造成功。
*/

struct Animal {
    let species: String
    init?(species: String) {
        if species.isEmpty {
            return nil
        }
        self.species = species
    }
}

/*
枚举类型的可失败构造器
你可以通过一个带一个或多个参数的可失败构造器来获取枚举类型中特定的枚举成员。如果提供的参数无法匹配任何枚举成员，则构造失败。
*/

enum TemperatureUnit {
    case Kelvin, Celsius, Fahrenheit
    init?(symbol: Character) {
        switch symbol {
        case "K":
            self = .Kelvin
        case "C":
            self = .Celsius
        case "F":
            self = .Fahrenheit
        default:
            return nil
        }
    }
}

/*
必要构造器
在类的构造器前添加 required 修饰符表明所有该类的子类都必须实现该构造器：

class SomeClass {
    required init() {
        // 构造器的实现代码
    }
}
在子类重写父类的必要构造器时，必须在子类的构造器前也添加 required 修饰符，表明该构造器要求也应用于继承链后面的子类。在重写父类中必要的指定构造器时，不需要添加 override 修饰符：

class SomeSubclass: SomeClass {
    required init() {
        // 构造器的实现代码
    }
}
注意

如果子类继承的构造器能满足必要构造器的要求，则无须在子类中显式提供必要构造器的实现。
*/


/*
下面模板介绍了如何用闭包为属性提供默认值：

class SomeClass {
    let someProperty: SomeType = {
        // 在这个闭包中给 someProperty 创建一个默认值
        // someValue 必须和 SomeType 类型相同
        return someValue
    }()
}
*/
