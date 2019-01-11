
/*
字典
字典是一种存储多个相同类型的值的容器。每个值（value）都关联唯一的键（key），键作为字典中的这个值数据的标识符。和数组中的数据项不同，字典中的数据项并没有具体顺序。我们在需要通过标识符（键）访问数据的时候使用字典，这种方法很大程度上和我们在现实世界中使用字典查字义的方法一样。

字典的内容理论上是无序的，遍历元素时的顺序是无法确定的。将元素插入字典的顺序并不会决定它们被遍历的顺序。
*/


// 创建一个空字典
// 我们可以像数组一样使用构造语法创建一个拥有确定类型的空字典：
 
var namesOfIntegers = [Int: String]()
// namesOfIntegers 是一个空的 [Int: String] 字典

/*
如果上下文已经提供了类型信息，我们可以使用空字典字面量来创建一个空字典，记作 [:]（中括号中放一个冒号）：
*/
namesOfIntegers[16] = "sixteen"
// namesOfIntegers 现在包含一个键值对
namesOfIntegers = [:]
// namesOfIntegers 又成为了一个 [Int: String] 类型的空字典

/*
用字典字面量创建字典
我们可以使用字典字面量来构造字典，这和我们刚才介绍过的数组字面量拥有相似语法。字典字面量是一种将一个或多个键值对写作 Dictionary 集合的快捷途径。
*/

//下面的例子创建了一个存储国际机场名称的字典。在这个字典中键是三个字母的国际航空运输相关代码，值是机场名称：

var airports: [String: String] = ["YYZ": "Toronto Pearson", "DUB": "Dublin"]

// 我们还可以使用下标语法来通过给某个键的对应值赋值为 nil 来从字典里移除一个键值对：

airports["APL"] = "Apple Internation"
// "Apple Internation" 不是真的 APL 机场，删除它
airports["APL"] = nil
// APL 现在被移除了

/*
字典遍历
我们可以使用 for-in 循环来遍历某个字典中的键值对。每一个字典中的数据项都以 (key, value) 元组形式返回，并且我们可以使用临时常量或者变量来分解这些元组：
*/
for (airportCode, airportName) in airports {
    print("\(airportCode): \(airportName)")
}
// YYZ: Toronto Pearson
// LHR: London Heathrow


// 通过访问 keys 或者 values 属性，我们也可以遍历字典的键或者值：

for airportCode in airports.keys {
    print("Airport code: \(airportCode)")
}
// Airport code: YYZ
// Airport code: LHR

for airportName in airports.values {
    print("Airport name: \(airportName)")
}
// Airport name: Toronto Pearson
// Airport name: London Heathrow

// 如果我们只是需要使用某个字典的键集合或者值集合来作为某个接受 Array 实例的 API 的参数，可以直接使用 keys 或者 values 属性构造一个新数组：

let airportCodes = [String](airports.keys)
// airportCodes 是 ["YYZ", "LHR"]

let airportNames = [String](airports.values)
// airportNames 是 ["Toronto Pearson", "London Heathrow"]

