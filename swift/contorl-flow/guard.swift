
// if 语句不好用吗 -_-!!


/*
提前退出
像 if 语句一样，guard 的执行取决于一个表达式的布尔值。我们可以使用 guard 语句来要求条件必须为真时，以执行 guard 语句后的代码。不同于 if 语句，一个 guard 语句总是有一个 else 从句，如果条件不为真则执行 else 从句中的代码。
*/

func greet(person: [String: String]) {
    guard let name = person["name"] else {
        return
    }
    print("Hello \(name)")
    guard let location = person["location"] else {
        print("I hope the weather is nice near you.")
        return
    }
    print("I hope the weather is nice in \(location).")
}
greet(["name": "John"])
// 输出 "Hello John!"
// 输出 "I hope the weather is nice near you."
greet(["name": "Jane", "location": "Cupertino"])
// 输出 "Hello Jane!"
// 输出 "I hope the weather is nice in Cupertino."

/*
如果 guard 语句的条件被满足，则继续执行 guard 语句大括号后的代码。将变量或者常量的可选绑定作为 guard 语句的条件，都可以保护 guard 语句后面的代码。

如果条件不被满足，在 else 分支上的代码就会被执行。这个分支必须转移控制以退出 guard 语句出现的代码段。它可以用控制转移语句如 return,break,continue 或者 throw 做这件事，或者调用一个不返回的方法或函数，例如 fatalError()。

相比于可以实现同样功能的 if 语句，按需使用 guard 语句会提升我们代码的可读性。它可以使你的代码连贯的被执行而不需要将它包在 else 块中，它可以使你在紧邻条件判断的地方，处理违规的情况。

*/

