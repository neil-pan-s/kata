
/*
使用可选链式调用代替强制展开
通过在想调用的属性、方法，或下标的可选值后面放一个问号（?），可以定义一个可选链。这一点很像在可选值后面放一个叹号（!）来强制展开它的值。它们的主要区别在于当可选值为空时可选链式调用只会调用失败，然而强制展开将会触发运行时错误。

为了反映可选链式调用可以在空值（nil）上调用的事实，不论这个调用的属性、方法及下标返回的值是不是可选值，它的返回结果都是一个可选值。你可以利用这个返回值来判断你的可选链式调用是否调用成功，如果调用有返回值则说明调用成功，返回 nil 则说明调用失败。

特别地，可选链式调用的返回结果与原本的返回结果具有相同的类型，但是被包装成了一个可选值。例如，使用可选链式调用访问属性，当可选链式调用成功时，如果属性原本的返回结果是 Int 类型，则会变为 Int? 类型。
*/

class Person {
    var residence: Residence?
}

class Residence {
    var numberOfRooms = 1
}


let john = Person()
// let roomCount = john.residence!.numberOfRooms
// 这会引发运行时错误

if let roomCount = john.residence?.numberOfRooms {
    print("John's residence has \(roomCount) room(s).")
} else {
    print("Unable to retrieve the number of rooms.")
}
// 打印 “Unable to retrieve the number of rooms.”

/*
访问可选类型的下标
如果下标返回可选类型值，比如 Swift 中 Dictionary 类型的键的下标，可以在下标的结尾括号后面放一个问号来在其可选返回值上进行可选链式调用：
*/

var testScores = ["Dave": [86, 82, 84], "Bev": [79, 94, 81]]
testScores["Dave"]?[0] = 91
testScores["Bev"]?[0] += 1
testScores["Brian"]?[0] = 72 // 不存在 Brian 赋值不会执行
// "Dave" 数组现在是 [91, 82, 84]，"Bev" 数组现在是 [80, 94, 81]


/*
连接多层可选链式调用
可以通过连接多个可选链式调用在更深的模型层级中访问属性、方法以及下标。然而，多层可选链式调用不会增加返回值的可选层级。

也就是说：

如果你访问的值不是可选的，可选链式调用将会返回可选值。
如果你访问的值就是可选的，可选链式调用不会让可选返回值变得“更可选”。
因此：

通过可选链式调用访问一个 Int 值，将会返回 Int?，无论使用了多少层可选链式调用。
类似的，通过可选链式调用访问 Int? 值，依旧会返回 Int? 值，并不会返回 Int??。
*/

if let beginsWithThe =
    john.residence?.address?.buildingIdentifier()?.hasPrefix("The") {
        if beginsWithThe {
            print("John's building identifier begins with \"The\".")
        } else {
            print("John's building identifier does not begin with \"The\".")
        }
}
// 打印 “John's building identifier begins with "The".”

