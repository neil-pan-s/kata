
/*
可选绑定
使用可选绑定（optional binding）来判断可选类型是否包含值，如果包含就把值赋给一个临时常量或者变量。可选绑定可以用在 if 和 while 语句中，这条语句不仅可以用来判断可选类型中是否有值，同时可以将可选类型中的值赋给一个常量或者变量。if 和 while 语句，请参考控制流。

像下面这样在 if 语句中写一个可选绑定：

if let constantName = someOptional {
    statements
}
*/

// 你可以像上面这样使用可选绑定来重写 在可选类型举出的 possibleNumber 例子：

var possibleNumber: String = "123"
possibleNumber = "hello"

if let actualNumber = Int(possibleNumber) {
    print("\'\(possibleNumber)\' has an integer value of \(actualNumber)")
} else {
    print("\'\(possibleNumber)\' could not be converted to an integer")
}
// 输出 "'123' has an integer value of 123"


