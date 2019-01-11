
/*
表示并抛出错误
在 Swift 中，错误用符合 Error 协议的类型的值来表示。这个空协议表明该类型可以用于错误处理。
*/

// Swift 的枚举类型尤为适合构建一组相关的错误状态，枚举的关联值还可以提供错误状态的额外信息。例如，你可以这样表示在一个游戏中操作自动贩卖机时可能会出现的错误状态：

enum VendingMachineError: Error {
    case invalidSelection                    //选择无效
    case insufficientFunds(coinsNeeded: Int) //金额不足
    case outOfStock                          //缺货
}

// 抛出一个错误可以让你表明有意外情况发生，导致正常的执行流程无法继续执行。抛出错误使用 throw 关键字。例如，下面的代码抛出一个错误，提示贩卖机还需要 5 个硬币：

throw VendingMachineError.insufficientFunds(coinsNeeded: 5)

/*
用 throwing 函数传递错误
为了表示一个函数、方法或构造器可以抛出错误，在函数声明的参数列表之后加上 throws 关键字。一个标有 throws 关键字的函数被称作throwing 函数。如果这个函数指明了返回值类型，throws 关键词需要写在箭头（->）的前面。

func canThrowErrors() throws -> String
func cannotThrowErrors() -> String
一个 throwing 函数可以在其内部抛出错误，并将错误传递到函数被调用时的作用域。

注意

只有 throwing 函数可以传递错误。任何在某个非 throwing 函数内部抛出的错误只能在函数内部处理。
*/

class VendingMachine {
  func vend(name: string) throws {
	throw VendingMachineError.outOfStock
  }
}


let favoriteSnacks = [
    "Alice": "Chips",
    "Bob": "Licorice",
    "Eve": "Pretzels",
]
func buyFavoriteSnack(person: String, vendingMachine: VendingMachine) throws {
    let snackName = favoriteSnacks[person] ?? "Candy Bar"
    try vendingMachine.vend(itemNamed: snackName)
}

/*
throwing 构造器能像 throwing 函数一样传递错误。例如下面代码中的 PurchasedSnack 构造器在构造过程中调用了 throwing 函数，并且通过传递到它的调用者来处理这些错误。
*/
struct PurchasedSnack {
    let name: String
    init(name: String, vendingMachine: VendingMachine) throws {
        try vendingMachine.vend(itemNamed: name)
        self.name = name
    }
}

/*
用 Do-Catch 处理错误
你可以使用一个 do-catch 语句运行一段闭包代码来处理错误。如果在 do 子句中的代码抛出了一个错误，这个错误会与 catch 子句做匹配，从而决定哪条子句能处理它。

下面是 do-catch 语句的一般形式：

do {
    try expression
    statements
} catch pattern 1 {
    statements
} catch pattern 2 where condition {
    statements
}
*/

var vendingMachine = VendingMachine()
vendingMachine.coinsDeposited = 8
do {
    try buyFavoriteSnack(person: "Alice", vendingMachine: vendingMachine)
} catch VendingMachineError.invalidSelection {
    print("Invalid Selection.")
} catch VendingMachineError.outOfStock {
    print("Out of Stock.")
} catch VendingMachineError.insufficientFunds(let coinsNeeded) {
    print("Insufficient funds. Please insert an additional \(coinsNeeded) coins.")
}
// 打印 “Insufficient funds. Please insert an additional 2 coins.”

/*
将错误转换成可选值
可以使用 try? 通过将错误转换成一个可选值来处理错误。如果在评估 try? 表达式时一个错误被抛出，那么表达式的值就是 nil。例如，在下面的代码中，x 和 y 有着相同的数值和等价的含义：
*/

func someThrowingFunction() throws -> Int {
    // ...
}

let x = try? someThrowingFunction()

let y: Int?
do {
    y = try someThrowingFunction()
} catch {
    y = nil
}

/*
如果你想对所有的错误都采用同样的方式来处理，用 try? 就可以让你写出简洁的错误处理代码。例如，下面的代码用几种方式来获取数据，如果所有方式都失败了则返回 nil。
*/

func fetchData() -> Data? {
    if let data = try? fetchDataFromDisk() { return data }
    if let data = try? fetchDataFromServer() { return data }
    return nil
}

/*
禁用错误传递
有时你知道某个 throwing 函数实际上在运行时是不会抛出错误的，在这种情况下，你可以在表达式前面写 try! 来禁用错误传递，这会把调用包装在一个不会有错误抛出的运行时断言中。如果真的抛出了错误，你会得到一个运行时错误。

例如，下面的代码使用了 loadImage(atPath:) 函数，该函数从给定的路径加载图片资源，如果图片无法载入则抛出一个错误。在这种情况下，因为图片是和应用绑定的，运行时不会有错误抛出，所以适合禁用错误传递。
*/
let photo = try! loadImage(atPath: "./Resources/John Appleseed.jpg")
