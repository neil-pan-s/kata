
/*
Swift 为不确定类型提供了两种特殊的类型别名：

Any 可以表示任何类型，包括函数类型。
AnyObject 可以表示任何类类型的实例。
只有当你确实需要它们的行为和功能时才使用 Any 和 AnyObject。当你期望你的代码可以工作，最好还是要确定类型。
*/

var things = [Any]()

things.append(0)
things.append(0.0)
things.append(42)
things.append(3.14159)
things.append("hello")
things.append((3.0, 5.0))
things.append(Movie(name: "Ghostbusters", director: "Ivan Reitman"))
things.append({ (name: String) -> String in "Hello, \(name)" })

/*
Any 类型可以表示所有类型的值，包括可选类型。Swift 会在你用 Any 类型来表示一个可选值的时候，给你一个警告。如果你确实想使用 Any 类型来承载可选值，你可以使用 as 操作符显式转换为 Any，如下所示：
*/

let optionalNumber: Int? = 3
things.append(optionalNumber)        // 警告
things.append(optionalNumber as Any) // 没有警告

