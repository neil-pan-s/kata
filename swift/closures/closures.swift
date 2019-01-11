/*
闭包是自包含的函数代码块，可以在代码中被传递和使用。Swift 中的闭包与 C 和 Objective-C 中的代码块（blocks）以及其他一些编程语言中的匿名函数比较相似。

闭包可以捕获和存储其所在上下文中任意常量和变量的引用。被称为包裹常量和变量。 Swift 会为你管理在捕获过程中涉及到的所有内存操作。

闭包采取如下三种形式之一：

全局函数是一个有名字但不会捕获任何值的闭包
嵌套函数是一个有名字并可以捕获其封闭函数域内值的闭包
闭包表达式是一个利用轻量级语法所写的可以捕获其上下文中变量或常量值的匿名闭包
Swift 的闭包表达式拥有简洁的风格，并鼓励在常见场景中进行语法优化，主要优化如下：

利用上下文推断参数和返回值类型
隐式返回单表达式闭包，即单表达式闭包可以省略 return 关键字
参数名称缩写
尾随闭包语法
*/


// 回调函数式闭包
let names = ["Chris", "Alex", "Ewa", "Barry", "Daniella"]
func backward(_ s1: String, _ s2: String) -> Bool {
    return s1 > s2
}
var reversedNames = names.sorted(by: backward)
// reversedNames 为 ["Ewa", "Daniella", "Chris", "Barry", "Alex"]

/*
闭包表达式
嵌套函数是一个在较复杂函数中方便进行命名和定义自包含代码模块的方式。当然，有时候编写小巧的没有完整定义和命名的类函数结构也是很有用处的，尤其是在你处理一些函数并需要将另外一些函数作为该函数的参数时。

闭包表达式是一种利用简洁语法构建内联闭包的方式。闭包表达式提供了一些语法优化，使得撰写闭包变得简单明了。

闭包表达式语法
闭包表达式语法有如下的一般形式：

{ (parameters) -> return type in
    statements
}
闭包表达式参数 可以是 in-out 参数，但不能设定默认值。如果你命名了可变参数，也可以使用此可变参数。元组也可以作为参数和返回值。

*/

// 下面的例子展示了之前 backward(_:_:) 函数对应的闭包表达式版本的代码：

reversedNames = names.sorted(by: { (s1: String, s2: String) -> Bool in
    return s1 > s2
})

/*
根据上下文推断类型

因为排序闭包函数是作为 sorted(by:) 方法的参数传入的，Swift 可以推断其参数和返回值的类型。
这意味着 (String, String) 和 Bool 类型并不需要作为闭包表达式定义的一部分。因为所有的类型都可以被正确推断，返回箭头（->）和围绕在参数周围的括号也可以被省略：
*/
reversedNames = names.sorted(by: { s1, s2 in return s1 > s2 } )

/*
单表达式闭包隐式返回
单行表达式闭包可以通过省略 return 关键字来隐式返回单行表达式的结果，如上版本的例子可以改写为：
*/
reversedNames = names.sorted(by: { s1, s2 in s1 > s2 } )

/*
运算符方法
实际上还有一种更简短的方式来编写上面例子中的闭包表达式。Swift 的 String 类型定义了关于大于号（>）的字符串实现，其作为一个函数接受两个 String 类型的参数并返回 Bool 类型的值。而这正好与 sorted(by:) 方法的参数需要的函数类型相符合。因此，你可以简单地传递一个大于号，Swift 可以自动推断出你想使用大于号的字符串函数实现：
*/
reversedNames = names.sorted(by: >)

/*
尾随闭包
如果你需要将一个很长的闭包表达式作为最后一个参数传递给函数，可以使用尾随闭包来增强函数的可读性。尾随闭包是一个书写在函数括号之后的闭包表达式，函数支持将其作为最后一个参数调用。在使用尾随闭包时，你不用写出它的参数标签：
*/
func someFunctionThatTakesAClosure(closure: () -> Void) {
    // 函数体部分
}

// 以下是不使用尾随闭包进行函数调用
someFunctionThatTakesAClosure(closure: {
    // 闭包主体部分
})

// 以下是使用尾随闭包进行函数调用
someFunctionThatTakesAClosure() {
    // 闭包主体部分
}
// 在闭包表达式语法一节中作为 sorted(by:) 方法参数的字符串排序闭包可以改写为：

reversedNames = names.sorted() { $0 > $1 }
// 如果闭包表达式是函数或方法的唯一参数，则当你使用尾随闭包时，你甚至可以把 () 省略掉：

reversedNames = names.sorted { $0 > $1 }

// 当闭包非常长以至于不能在一行中进行书写时，尾随闭包变得非常有用

let digitNames = [
    0: "Zero", 1: "One", 2: "Two",   3: "Three", 4: "Four",
    5: "Five", 6: "Six", 7: "Seven", 8: "Eight", 9: "Nine"
]
let numbers = [16, 58, 510]

let strings = numbers.map {
    (number) -> String in
    var number = number
    var output = ""
    repeat {
        output = digitNames[number % 10]! + output
        number /= 10
    } while number > 0
    return output
}
// strings 常量被推断为字符串类型数组，即 [String]
// 其值为 ["OneSix", "FiveEight", "FiveOneZero"]

/*
值捕获
闭包可以在其被定义的上下文中捕获常量或变量。即使定义这些常量和变量的原作用域已经不存在，闭包仍然可以在闭包函数体内引用和修改这些值。

Swift 中，可以捕获值的闭包的最简单形式是嵌套函数，也就是定义在其他函数的函数体内的函数。嵌套函数可以捕获其外部函数所有的参数以及定义的常量和变量。
*/

func makeIncrementer(forIncrement amount: Int) -> () -> Int {
    var runningTotal = 0
    func incrementer() -> Int {
        runningTotal += amount
        return runningTotal
    }
    return incrementer
}

let incrementByTen = makeIncrementer(forIncrement: 10)
let incrementBySeven = makeIncrementer(forIncrement: 7)

/*
逃逸闭包
当一个闭包作为参数传到一个函数中，但是这个闭包在函数返回之后才被执行，我们称该闭包从函数中逃逸。当你定义接受闭包作为参数的函数时，你可以在参数名之前标注 @escaping，用来指明这个闭包是允许“逃逸”出这个函数的。
*/

var completionHandlers: [() -> Void] = []
func someFunctionWithEscapingClosure(completionHandler: @escaping () -> Void) {
    completionHandlers.append(completionHandler)
}

func someFunctionWithNonescapingClosure(closure: () -> Void) {
    closure()
}

class SomeClass {
    var x = 10
    func doSomething() {
        someFunctionWithEscapingClosure { self.x = 100 }
        someFunctionWithNonescapingClosure { x = 200 }
    }
}

let instance = SomeClass()
instance.doSomething()
print(instance.x)
// 打印出 "200"

completionHandlers.first?()
print(instance.x)
// 打印出 "100"


/*
自动闭包
自动闭包是一种自动创建的闭包，用于包装传递给函数作为参数的表达式。这种闭包不接受任何参数，当它被调用的时候，会返回被包装在其中的表达式的值。这种便利语法让你能够省略闭包的花括号，用一个普通的表达式来代替显式的闭包。
*/

var customersInLine = ["Chris", "Alex", "Ewa", "Barry", "Daniella"]
print(customersInLine.count)
// 打印出 "5"

let customerProvider = { customersInLine.remove(at: 0) }
print(customersInLine.count)
// 打印出 "5"

print("Now serving \(customerProvider())!")
// Prints "Now serving Chris!"
print(customersInLine.count)
// 打印出 "4"

/*
@autoclosure 通过将参数标记为 @autoclosure , 参数将自动转化为一个闭包.
*/

// customersInLine is ["Ewa", "Barry", "Daniella"]
func serve(customer customerProvider: @autoclosure () -> String) {
    print("Now serving \(customerProvider())!")
}
serve(customer: customersInLine.remove(at: 0))
// 打印 "Now serving Ewa!"


/*
闭包让你能够延迟求值，因为直到你调用这个闭包，代码段才会被执行。延迟求值对于那些有副作用（Side Effect）和高计算成本的代码来说是很有益处的，因为它使得你能控制代码的执行时机。
*/

