
/*
使用断言进行调试
你可以调用 Swift 标准库的 assert(_:_:file:line:) 函数来写一个断言。向这个函数传入一个结果为 true 或者 false 的表达式以及一条信息，当表达式的结果为 false 的时候这条信息会被显示
*/

// let age = -3
let age = 3
assert(age >= 0, "A person's age cannot be less than zero")
// 因为 age < 0，所以断言会触发


// 如果不需要断言信息，可以就像这样忽略掉：
assert(age >= 0)

// 也可以不进行判断 直接触发
// assertionFailure("A person's age can't be less than zero.")


/*
强制执行先决条件
当一个条件可能为假，但是继续执行代码要求条件必须为真的时候，需要使用先决条件。例
如使用先决条件来检查是否下标越界，或者来检查是否将一个正确的参数传给函数。

*/

precondition(1 > 0, "Index must be greater than zero.")
// precondition(-1 > 0, "Index must be greater than zero.")


/*
注意

如果你使用 unchecked 模式（-Ounchecked）编译代码，先决条件将不会进行检查。编译器假设所有的先决条件总是为 true（真），他将优化你的代码。然而，fatalError(_:file:line:) 函数总是中断执行，无论你怎么进行优化设定。

你能使用 fatalError(_:file:line:) 函数在设计原型和早期开发阶段，这个阶段只有方法的声明，但是没有具体实现，你可以在方法体中写上 fatalError("Unimplemented")作为具体实现。因为 fatalError 不会像断言和先决条件那样被优化掉，所以你可以确保当代码执行到一个没有被实现的方法时，程序会被中断。
*/


