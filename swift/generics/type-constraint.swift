
/*
类型约束语法
你可以在一个类型参数名后面放置一个类名或者协议名，并用冒号进行分隔，来定义类型约束，它们将成为类型参数列表的一部分。对泛型函数添加类型约束的基本语法如下所示（作用于泛型类型时的语法与之相同）：

func someFunction<T: SomeClass, U: SomeProtocol>(someT: T, someU: U) {
    // 这里是泛型函数的函数体部分
}
*/

// 类型约束实践
// 这里有个名为 findIndex(ofString:in:) 的非泛型函数，该函数的功能是在一个 String 数组中查找给定 String 值的索引。若查找到匹配的字符串，findIndex(ofString:in:) 函数返回该字符串在数组中的索引值，否则返回 nil：

func findIndex(ofString valueToFind: String, in array: [String]) -> Int? {
    for (index, value) in array.enumerated() {
        if value == valueToFind {
            return index
        }
    }
    return nil
}

// findIndex(ofString:in:) 函数可以用于查找字符串数组中的某个字符串：

let strings = ["cat", "dog", "llama", "parakeet", "terrapin"]
if let foundIndex = findIndex(ofString: "llama", in: strings) {
    print("The index of llama is \(foundIndex)")
}
// 打印 “The index of llama is 2”

// generics version 1: 

/*
上面所写的函数无法通过编译。问题出在相等性检查上，即 "if value == valueToFind"。不是所有的 Swift 类型都可以用等式符（==）进行比较。比如说，如果你创建一个自定义的类或结构体来表示一个复杂的数据模型，那么 Swift 无法猜到对于这个类或结构体而言“相等”意味着什么。
*/

func findIndex<T>(of valueToFind: T, in array:[T]) -> Int? {
    for (index, value) in array.enumerated() {
        if value == valueToFind {
            return index
        }
    }
    return nil
}

/*
Swift 标准库中定义了一个 Equatable 协议，该协议要求任何遵循该协议的类型必须实现等式符（==）及不等符（!=），从而能对该类型的任意两个值进行比较。所有的 Swift 标准类型自动支持 Equatable 协议。

任何 Equatable 类型都可以安全地使用在 findIndex(of:in:) 函数中，因为其保证支持等式操作符。为了说明这个事实，当你定义一个函数时，你可以定义一个 Equatable 类型约束作为类型参数定义的一部分：
*/

// generics version 2

func findIndex<T: Equatable>(of valueToFind: T, in array:[T]) -> Int? {
    for (index, value) in array.enumerated() {
        if value == valueToFind {
            return index
        }
    }
    return nil
}

let doubleIndex = findIndex(of: 9.3, in: [3.14159, 0.1, 0.25])
// doubleIndex 类型为 Int?，其值为 nil，因为 9.3 不在数组中
let stringIndex = findIndex(of: "Andrea", in: ["Mike", "Malcolm", "Andrea"])
// stringIndex 类型为 Int?，其值为 2

