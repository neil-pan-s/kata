

// 通过检查其 Bool 类型的 isEmpty 属性来判断该字符串是否为空：

let emptyString = ""

if emptyString.isEmpty {
    print("Nothing to see here")
}
// 打印输出："Nothing to see here"


// 通过 for-in 循环来遍历字符串，获取字符串中每一个字符的值：

for character in "Dog!\u{1F425}" {
    print(character)
}
// D
// o
// g
// !
// 🐶

/*
字符串插值
字符串插值是一种构建新字符串的方式，可以在其中包含常量、变量、字面量和表达式。字符串字面量和多行字符串字面量都可以使用字符串插值。 您插入的字符串字面量的每一项都在以反斜线为前缀的圆括号中：
*/

let multiplier = 3
let message = "\(multiplier) times 2.5 is \(Double(multiplier) * 2.5)"
// message 是 "3 times 2.5 is 7.5"


var welcome = "hello"
welcome.append(" world")
welcome.insert("!", at: welcome.endIndex)
welcome.insert(contentsOf: " there", at: welcome.index(before: welcome.endIndex))

print(welcome)

welcome.remove(at: welcome.index(before: welcome.endIndex))
// welcome 现在等于 "hello there"

let range = welcome.index(welcome.endIndex, offsetBy: -6)..<welcome.endIndex
welcome.removeSubrange(range)
// welcome 现在等于 "hello"

/* 哇哇哇 JS一个slice  */





