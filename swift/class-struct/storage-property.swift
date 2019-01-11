
/*
存储属性
简单来说，一个存储属性就是存储在特定类或结构体实例里的一个常量或变量。存储属性可以是变量存储属性（用关键字 var 定义），也可以是常量存储属性（用关键字 let 定义）。
*/

struct FixedLengthRange {
    var firstValue: Int
    let length: Int
}
var rangeOfThreeItems = FixedLengthRange(firstValue: 0, length: 3)
// 该区间表示整数0，1，2
rangeOfThreeItems.firstValue = 6
// 该区间现在表示整数6，7，8
// FixedLengthRange 的实例包含一个名为 firstValue 的变量存储属性和一个名为 length 的常量存储属性。在上面的例子中，length 在创建实例的时候被初始化，因为它是一个常量存储属性，所以之后无法修改它的值。

/*
常量结构体的存储属性
如果创建了一个结构体的实例并将其赋值给一个常量，则无法修改该实例的任何属性，即使有属性被声明为变量也不行：
*/

let rangeOfFourItems = FixedLengthRange(firstValue: 0, length: 4)
// 该区间表示整数0，1，2，3
rangeOfFourItems.firstValue = 6
// 尽管 firstValue 是个变量属性，这里还是会报错



