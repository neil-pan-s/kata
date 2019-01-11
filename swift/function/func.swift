
/* 
函数的定义与调用 

所有的这些信息汇总起来成为函数的定义，并以 func 作为前缀。指定函数返回类型时，用返回箭头 ->（一个连字符后跟一个右尖括号）后跟返回类型的名称的方式来表示。
*/

func greet(person: String) -> String {
    let greeting = "Hello, " + person + "!"
    return greeting
}

// 该定义描述了函数的功能，它期望接收什么作为参数和执行结束时它返回的结果是什么类型。这样的定义使得函数可以在别的地方以一种清晰的方式被调用：

print(greet(person: "Anna"))
// 打印 "Hello, Anna!"
print(greet(person: "Brian"))
// 打印 "Hello, Brian!"


func greet(person: String) {
    print("Hello, \(person)!")
}
/*
严格上来说，虽然没有返回值被定义，greet(person:) 函数依然返回了值。没有定义返回类型的函数会返回一个特殊的 Void 值。它其实是一个空的元组，没有任何元素，可以写成 ()。
*/


/*
多重返回值函数
你可以用元组（tuple）类型让多个值作为一个复合值从函数中返回。

下例中定义了一个名为 minMax(array:) 的函数，作用是在一个 Int 类型的数组中找出最小值与最大值。
*/
func minMax(array: [Int]) -> (min: Int, max: Int) {
    var currentMin = array[0]
    var currentMax = array[0]
    for value in array[1..<array.count] {
        if value < currentMin {
            currentMin = value
        } else if value > currentMax {
            currentMax = value
        }
    }
    return (currentMin, currentMax)
}

/* 
可选元组返回类型
如果函数返回的元组类型有可能整个元组都“没有值”，你可以使用可选的 元组返回类型反映整个元组可以是 nil 的事实。你可以通过在元组类型的右括号后放置一个问号来定义一个可选元组，例如 (Int, Int)? 或 (String, Int, Bool)?
*/

func minMax(array: [Int]) -> (min: Int, max: Int)? {
    if array.isEmpty { return nil }
    var currentMin = array[0]
    var currentMax = array[0]
    for value in array[1..<array.count] {
        if value < currentMin {
            currentMin = value
        } else if value > currentMax {
            currentMax = value
        }
    }
    return (currentMin, currentMax)
}

/* 
函数参数标签和参数名称

每个函数参数都有一个参数标签（argument label）以及一个参数名称（parameter name）。
参数标签在调用函数的时候使用；调用的时候需要将函数的参数标签写在对应的参数前面。参数名称在函数的实现中使用。
默认情况下，函数参数使用参数名称来作为它们的参数标签。

*/

// 指定参数标签
// 你可以在参数名称前指定它的参数标签，中间以空格分隔：

func someFunction(argumentLabel parameterName: Int) {
    // 在函数体内，parameterName 代表参数值
}
someFunction(argumentLabel: 9527)


// 忽略参数标签
// 如果你不希望为某个参数添加一个标签，可以使用一个下划线（_）来代替一个明确的参数标签。

func someFunction(_ parameterName: Int) {
    // 在函数体内，parameterName 代表参数值
}
someFunction(9527)

/*
默认参数值
你可以在函数体中通过给参数赋值来为任意一个参数定义默认值（Deafult Value）。当默认值被定义后，调用这个函数时可以忽略这个参数。
*/

func someFunction(parameterWithoutDefault: Int, parameterWithDefault: Int = 12) {
    // 如果你在调用时候不传第二个参数，parameterWithDefault 会值为 12 传入到函数体中。
}
someFunction(parameterWithoutDefault: 3, parameterWithDefault: 6) // parameterWithDefault = 6
someFunction(parameterWithoutDefault: 4) // parameterWithDefault = 12

/*
可变参数
一个可变参数（variadic parameter）可以接受零个或多个值。函数调用时，你可以用可变参数来指定函数参数可以被传入不确定数量的输入值。通过在变量类型名后面加入（...）的方式来定义可变参数。
*/

func arithmeticMean(_ numbers: Double...) -> Double {
    var total: Double = 0
    for number in numbers {
        total += number
    }
    return total / Double(numbers.count)
}
arithmeticMean(1, 2, 3, 4, 5)
// 返回 3.0, 是这 5 个数的平均数。
arithmeticMean(3, 8.25, 18.75)
// 返回 10.0, 是这 3 个数的平均数。

/*
输入输出参数
函数参数默认是常量。试图在函数体中更改参数值将会导致编译错误。这意味着你不能错误地更改参数值。如果你想要一个函数可以修改参数的值，并且想要在这些修改在函数调用结束后仍然存在，那么就应该把这个参数定义为输入输出参数（In-Out Parameters）。

定义一个输入输出参数时，在参数定义前加 inout 关键字。一个 输入输出参数有传入函数的值，这个值被函数修改，然后被传出函数，替换原来的值。想获取更多的关于输入输出参数的细节和相关的编译器优化，请查看输入输出参数一节。

你只能传递变量给输入输出参数。你不能传入常量或者字面量，因为这些量是不能被修改的。当传入的参数作为输入输出参数时，需要在参数名前加 & 符，表示这个值可以被函数修改。
*/

下例中，swapTwoInts(_:_:) 函数有两个分别叫做 a 和 b 的输入输出参数：

func swapTwoInts(_ a: inout Int, _ b: inout Int) {
    let temporaryA = a
    a = b
    b = temporaryA
}

/*
函数类型
每个函数都有种特定的函数类型，函数的类型由函数的参数类型和返回类型组成。

例如：
*/

func addTwoInts(_ a: Int, _ b: Int) -> Int {
    return a + b
}
func multiplyTwoInts(_ a: Int, _ b: Int) -> Int {
    return a * b
}
/*
这个例子中定义了两个简单的数学函数：addTwoInts 和 multiplyTwoInts。这两个函数都接受两个 Int 值， 返回一个 Int 值。

这两个函数的类型是 (Int, Int) -> Int，可以解读为:

“这个函数类型有两个 Int 型的参数并返回一个 Int 型的值”。

下面是另一个例子，一个没有参数，也没有返回值的函数：
*/
func printHelloWorld() {
    print("hello, world")
}
// 这个函数的类型是：() -> Void，或者叫“没有参数，并返回 Void 类型的函数”。

/*
使用函数类型
在 Swift 中，使用函数类型就像使用其他类型一样。例如，你可以定义一个类型为函数的常量或变量，并将适当的函数赋值给它：
*/

var mathFunction: (Int, Int) -> Int = addTwoInts
print("Result: \(mathFunction(2, 3))")
// Prints "Result: 5"

/*
函数类型作为参数类型
你可以用 (Int, Int) -> Int 这样的函数类型作为另一个函数的参数类型。这样你可以将函数的一部分实现留给函数的调用者来提供。

下面是另一个例子，正如上面的函数一样，同样是输出某种数学运算结果：
*/
func printMathResult(_ mathFunction: (Int, Int) -> Int, _ a: Int, _ b: Int) {
    print("Result: \(mathFunction(a, b))")
}
printMathResult(addTwoInts, 3, 5)
// 打印 "Result: 8"

/*
嵌套函数
到目前为止本章中你所见到的所有函数都叫全局函数（global functions），它们定义在全局域中。你也可以把函数定义在别的函数体中，称作 嵌套函数（nested functions）。

默认情况下，嵌套函数是对外界不可见的，但是可以被它们的外围函数（enclosing function）调用。一个外围函数也可以返回它的某一个嵌套函数，使得这个函数可以在其他域中被使用。

你可以用返回嵌套函数的方式重写 chooseStepFunction(backward:) 函数：
*/
func chooseStepFunction(backward: Bool) -> (Int) -> Int {
    func stepForward(input: Int) -> Int { return input + 1 }
    func stepBackward(input: Int) -> Int { return input - 1 }
    return backward ? stepBackward : stepForward
}



