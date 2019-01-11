
/*
创建一个空数组
我们可以使用构造语法来创建一个由特定数据类型构成的空数组：
*/

// var someInts = Array<Int>()
var someInts = [Int]()
print("someInts is of type [Int] with \(someInts.count) items.")
// 打印 "someInts is of type [Int] with 0 items."

someInts.append(3)
// someInts 现在包含一个 Int 值
someInts = []
// someInts 现在是空数组，但是仍然是 [Int] 类型的。

/*
创建一个带有默认值的数组
Swift 中的 Array 类型还提供一个可以创建特定大小并且所有数据都被默认的构造方法。我们可以把准备加入新数组的数据项数量（count）和适当类型的初始值（repeating）传入数组构造函数：
*/

var threeDoubles = Array(repeating: 0.0, count: 3)
// threeDoubles 是一种 [Double] 数组，等价于 [0.0, 0.0, 0.0]

/*
通过两个数组相加创建一个数组
我们可以使用加法操作符（+）来组合两种已存在的相同类型数组。新数组的数据类型会被从两个数组的数据类型中推断出来：
*/
var anotherThreeDoubles = Array(repeating: 2.5, count: 3)
// anotherThreeDoubles 被推断为 [Double]，等价于 [2.5, 2.5, 2.5]

var sixDoubles = threeDoubles + anotherThreeDoubles
// sixDoubles 被推断为 [Double]，等价于 [0.0, 0.0, 0.0, 2.5, 2.5, 2.5]

/*
用数组字面量构造数组
我们可以使用数组字面量来进行数组构造，这是一种用一个或者多个数值构造数组的简单方法。数组字面量是一系列由逗号分割并由方括号包含的数值：

[value 1, value 2, value 3]。
*/

// 下面这个例子创建了一个叫做 shoppingList 并且存储 String 的数组：

var shoppingList: [String] = ["Eggs", "Milk"]
// shoppingList 已经被构造并且拥有两个初始项。

shoppingList[0...1] = ["Bananas", "Apples"]
// shoppingList 修改

shoppingList.insert("Maple Syrup", at: 2)
let mapleSyrup = shoppingList.remove(at: 2)
let apples = shoppingList.removeLast()
print(mapleSyrup, apples)

// 数组遍历
for (index, value) in shoppingList. enumerated() {
    print("Item \(String(index + 1)): \(value)")
}


