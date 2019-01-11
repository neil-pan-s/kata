
/*
运算符函数
类和结构体可以为现有的运算符提供自定义的实现，这通常被称为运算符重载。

下面的例子展示了如何为自定义的结构体实现加法运算符（+）。算术加法运算符是一个双目运算符，因为它可以对两个值进行运算，同时它还是中缀运算符，因为它出现在两个值中间。

例子中定义了一个名为 Vector2D 的结构体用来表示二维坐标向量 (x, y)，紧接着定义了一个可以对两个 Vector2D 结构体进行相加的运算符函数：

struct Vector2D {
    var x = 0.0, y = 0.0
}

extension Vector2D {
    static func + (left: Vector2D, right: Vector2D) -> Vector2D {
        return Vector2D(x: left.x + right.x, y: left.y + right.y)
    }
}
该运算符函数被定义为 Vector2D 上的一个类方法，并且函数的名字与它要进行重载的 + 名字一致。因为加法运算并不是一个向量必需的功能，所以这个类方法被定义在 Vector2D 的一个扩展中，而不是 Vector2D 结构体声明内。而算术加法运算符是双目运算符，所以这个运算符函数接收两个类型为 Vector2D 的参数，同时有一个 Vector2D 类型的返回值。

在这个实现中，输入参数分别被命名为 left 和 right，代表在 + 运算符左边和右边的两个 Vector2D 实例。函数返回了一个新的 Vector2D 实例，这个实例的 x 和 y 分别等于作为参数的两个实例的 x 和 y 的值之和。

这个类方法可以在任意两个 Vector2D 实例中间作为中缀运算符来使用：

let vector = Vector2D(x: 3.0, y: 1.0)
let anotherVector = Vector2D(x: 2.0, y: 4.0)
let combinedVector = vector + anotherVector
// combinedVector 是一个新的 Vector2D 实例，值为 (5.0, 5.0)
这个例子实现两个向量 (3.0，1.0) 和 (2.0，4.0) 的相加，并得到新的向量 (5.0，5.0)。这个过程如下图示：

Art/vectorAddition_2x.png


前缀和后缀运算符
上个例子演示了一个双目中缀运算符的自定义实现。类与结构体也能提供标准单目运算符的实现。单目运算符只运算一个值。当运算符出现在值之前时，它就是前缀的（例如 -a），而当它出现在值之后时，它就是后缀的（例如 b!）。

要实现前缀或者后缀运算符，需要在声明运算符函数的时候在 func 关键字之前指定 prefix 或者 postfix 修饰符：

extension Vector2D {
    static prefix func - (vector: Vector2D) -> Vector2D {
        return Vector2D(x: -vector.x, y: -vector.y)
    }
}
这段代码为 Vector2D 类型实现了单目负号运算符。由于该运算符是前缀运算符，所以这个函数需要加上 prefix 修饰符。

对于简单数值，单目负号运算符可以对它们的正负性进行改变。对于 Vector2D 来说，该运算将其 x 和 y 属性的正负性都进行了改变：

let positive = Vector2D(x: 3.0, y: 4.0)
let negative = -positive
// negative 是一个值为 (-3.0, -4.0) 的 Vector2D 实例
let alsoPositive = -negative
// alsoPositive 是一个值为 (3.0, 4.0) 的 Vector2D 实例

复合赋值运算符
复合赋值运算符将赋值运算符（=）与其它运算符进行结合。例如，将加法与赋值结合成加法赋值运算符（+=）。在实现的时候，需要把运算符的左参数设置成 inout 类型，因为这个参数的值会在运算符函数内直接被修改。

extension Vector2D {
    static func += (left: inout Vector2D, right: Vector2D) {
        left = left + right
    }
}
因为加法运算在之前已经定义过了，所以在这里无需重新定义。在这里可以直接利用现有的加法运算符函数，用它来对左值和右值进行相加，并再次赋值给左值：

var original = Vector2D(x: 1.0, y: 2.0)
let vectorToAdd = Vector2D(x: 3.0, y: 4.0)
original += vectorToAdd
// original 的值现在为 (4.0, 6.0)
注意

不能对默认的赋值运算符（=）进行重载。只有组合赋值运算符可以被重载。同样地，也无法对三目条件运算符 （a ? b : c） 进行重载。


等价运算符
自定义的类和结构体没有对等价运算符进行默认实现，等价运算符通常被称为“相等”运算符（==）与“不等”运算符（!=）。对于自定义类型，Swift 无法判断其是否“相等”，因为“相等”的含义取决于这些自定义类型在你的代码中所扮演的角色。

为了使用等价运算符能对自定义的类型进行判等运算，需要为其提供自定义实现，实现的方法与其它中缀运算符一样, 并且增加对标准库 Equatable 协议的遵循：

extension Vector2D: Equatable {
    static func == (left: Vector2D, right: Vector2D) -> Bool {
        return (left.x == right.x) && (left.y == right.y)
    }
}
上述代码实现了“相等”运算符（==）来判断两个 Vector2D 实例是否相等。对于 Vector2D 类型来说，“相等”意味着“两个实例的 x 属性和 y 属性都相等”，这也是代码中用来进行判等的逻辑。示例里同时也实现了“不等”运算符（!=），它简单地将“相等”运算符的结果进行取反后返回。

现在我们可以使用这两个运算符来判断两个 Vector2D 实例是否相等：

let twoThree = Vector2D(x: 2.0, y: 3.0)
let anotherTwoThree = Vector2D(x: 2.0, y: 3.0)
if twoThree == anotherTwoThree {
    print("These two vectors are equivalent.")
}
// 打印 “These two vectors are equivalent.”
Swift 为以下自定义类型提等价运算符供合成实现：

只拥有遵循 Equatable 协议存储属性的结构体；
只拥有遵循 Equatable 协议关联类型的枚举；
没有关联类型的枚举。
在类型原本的声明中声明遵循 Equatable 来接收这些默认实现。

下面为三维位置向量 (x, y, z) 定义的 Vector3D 结构体，与 Vector2D 类似，由于 x，y 和 z 属性都是 Equatable 类型，Vector3D 就收到默认的等价运算符实现了。

struct Vector3D: Equatable {
    var x = 0.0, y = 0.0, z = 0.0
}

let twoThreeFour = Vector3D(x: 2.0, y: 3.0, z: 4.0)
let anotherTwoThreeFour = Vector3D(x: 2.0, y: 3.0, z: 4.0)
if twoThreeFour == anotherTwoThreeFour {
    print("These two vectors are also equivalent.")
}
// Prints "These two vectors are also equivalent."

自定义运算符
除了实现标准运算符，在 Swift 中还可以声明和实现自定义运算符。可以用来自定义运算符的字符列表请参考运算符。

新的运算符要使用 operator 关键字在全局作用域内进行定义，同时还要指定 prefix、infix 或者 postfix 修饰符：

prefix operator +++
上面的代码定义了一个新的名为 +++ 的前缀运算符。对于这个运算符，在 Swift 中并没有意义，因此我们针对 Vector2D 的实例来定义它的意义。对这个示例来讲，+++ 被实现为“前缀双自增”运算符。它使用了前面定义的复合加法运算符来让矩阵对自身进行相加，从而让 Vector2D 实例的 x 属性和 y 属性的值翻倍。实现 +++ 运算符的方式如下：

extension Vector2D {
    static prefix func +++ (vector: inout Vector2D) -> Vector2D {
        vector += vector
        return vector
    }
}

var toBeDoubled = Vector2D(x: 1.0, y: 4.0)
let afterDoubling = +++toBeDoubled
// toBeDoubled 现在的值为 (2.0, 8.0)
// afterDoubling 现在的值也为 (2.0, 8.0)

自定义中缀运算符的优先级
每个自定义中缀运算符都属于某个优先级组。这个优先级组指定了这个运算符和其他中缀运算符的优先级和结合性。优先级和结合性中详细阐述了这两个特性是如何对中缀运算符的运算产生影响的。

而没有明确放入优先级组的自定义中缀运算符会放到一个默认的优先级组内，其优先级高于三元运算符。

以下例子定义了一个新的自定义中缀运算符 +-，此运算符属于 AdditionPrecedence 优先组：

infix operator +-: AdditionPrecedence
extension Vector2D {
    static func +- (left: Vector2D, right: Vector2D) -> Vector2D {
        return Vector2D(x: left.x + right.x, y: left.y - right.y)
    }
}
let firstVector = Vector2D(x: 1.0, y: 2.0)
let secondVector = Vector2D(x: 3.0, y: 4.0)
let plusMinusVector = firstVector +- secondVector
// plusMinusVector 是一个 Vector2D 实例，并且它的值为 (4.0, -2.0)
这个运算符把两个向量的 x 值相加，同时用第一个向量的 y 值减去第二个向量的 y 值。因为它本质上是属于“相加型”运算符，所以将它放置 + 和 - 等默认的中缀“相加型”运算符相同的优先级组中。关于 Swift 标准库提供的运算符，以及完整的运算符优先级组和结合性设置，请参考 Swift Standard Library Operators Reference。而更多关于优先级组以及自定义操作符和优先级组的语法，请参考运算符声明

注意

当定义前缀与后缀运算符的时候，我们并没有指定优先级。然而，如果对同一个值同时使用前缀与后缀运算符，则后缀运算符会先参与运算。


*/

