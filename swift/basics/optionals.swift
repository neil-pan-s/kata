
/*
可选类型
使用可选类型（optionals）来处理值可能缺失的情况。可选类型表示两种可能： 或者有值， 你可以解析可选类型访问这个值， 或者根本没有值。

注意

C 和 Objective-C 中并没有可选类型这个概念。最接近的是 Objective-C 中的一个特性，一个方法要不返回一个对象要不返回 nil，nil 表示“缺少一个合法的对象”。然而，这只对对象起作用——对于结构体，基本的 C 类型或者枚举类型不起作用。对于这些类型，Objective-C 方法一般会返回一个特殊值（比如 NSNotFound）来暗示值缺失。这种方法假设方法的调用者知道并记得对特殊值进行判断。然而，Swift 的可选类型可以让你暗示任意类型的值缺失，并不需要一个特殊值。

*/


let possibleNumber = "123"
let convertedNumber = Int(possibleNumber)
// convertedNumber 被推测为类型 "Int?"， 或者类型 "optional Int"


/*
因为该构造器可能会失败，所以它返回一个可选类型（optional）Int，而不是一个 Int。一个可选的 Int 被写作 Int? 而不是 Int。问号暗示包含的值是可选类型，也就是说可能包含 Int 值也可能不包含值。（不能包含其他任何值比如 Bool 值或者 String 值。只能是 Int 或者什么都没有。）
*/

/*
当你确定可选类型确实包含值之后，你可以在可选的名字后面加一个感叹号（!）来获取值。这个惊叹号表示“我知道这个可选有值，请使用它。”这被称为可选值的强制解析（forced unwrapping）：
*/

var a: Int? = 1
// > a
// $R5: Int? = 1
// > a!
// $R6: Int = 1

var b: Int? = nil
// > a!
// throw error







