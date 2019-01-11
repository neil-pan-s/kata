
/*
wift 提供了8、16、32和64位的有符号和无符号整数类型。这些整数类型和 C 语言的命名方式很像，比如8位无符号整数类型是 UInt8，32位有符号整数类型是 Int32 。

一般来说，你不需要专门指定整数的长度。Swift 提供了一个特殊的整数类型 Int，长度与当前平台的原生字长相同：

在32位平台上，Int 和 Int32 长度相同。
在64位平台上，Int 和 Int64 长度相同。
除非你需要特定长度的整数，一般来说使用 Int 就够了。

Swift 也提供了一个特殊的无符号类型 UInt，长度与当前平台的原生字长相同：

在32位平台上，UInt 和 UInt32 长度相同。
在64位平台上，UInt 和 UInt64 长度相同。
注意

尽量不要使用 UInt，除非你真的需要存储一个和当前平台原生字长相同的无符号整数。除了这种情况，最好使用 Int，即使你要存储的值已知是非负的。统一使用 Int 可以提高代码的可复用性，避免不同类型数字之间的转换，并且匹配数字的类型推断
*/

let min = UInt8.min
let max = UInt8.max 

print(min, max)

let cannotBeNegative: UInt8 = -1
// UInt8 类型不能存储负数，所以会报错
let tooBig: Int8 = Int8.max + 1
// Int8 类型不能存储超过最大值的数，所以会报错


/*
数值型字面量
整数字面量可以被写作：

一个十进制数，没有前缀
一个二进制数，前缀是 0b
一个八进制数，前缀是 0o
一个十六进制数，前缀是 0x
*/


// 下面的所有整数字面量的十进制值都是 17:
let decimalInteger = 17
let binaryInteger = 0b10001       // 二进制的17
let octalInteger = 0o21           // 八进制的17
let hexadecimalInteger = 0x11     // 十六进制的17




