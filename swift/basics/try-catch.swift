
/*
错误处理
你可以使用 错误处理（error handling） 来应对程序执行中可能会遇到的错误条件。

相对于可选中运用值的存在与缺失来表达函数的成功与失败，错误处理可以推断失败的原因，并传播至程序的其他部分。

当一个函数遇到错误条件，它能报错。调用函数的地方能抛出错误消息并合理处理。

*/

func canThrowAnError() throws {
    // 这个函数有可能抛出错误
}

// 一个函数可以通过在声明中添加 throws 关键词来抛出错误消息。当你的函数能抛出错误消息时，你应该在表达式中前置 try 关键词。

do {
    try canThrowAnError()
    // 没有错误消息抛出
} catch {
    // 有一个错误消息抛出
}

// 一个 do 语句创建了一个新的包含作用域，使得错误能被传播到一个或多个 catch 从句。

// 这里有一个错误处理如何用来应对不同错误条件的例子。

enum SandwichError: Error {
    case outOfCleanDishes
    case missingIngredients(ingredients: Int) 
}

func makeASandwich() throws {
    // ...
}

do {
    try makeASandwich()
    print("eatASandwich")
} catch SandwichError.outOfCleanDishes {
    print("washDishes")
} catch SandwichError.missingIngredients(let ingredients) {
    print("buyGroceries \(ingredients)")
}

