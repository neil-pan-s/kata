
/*
在扩展里添加协议遵循

即便无法修改源代码，依然可以通过扩展令已有类型遵循并符合协议。扩展可以为已有类型添加属性、方法、下标以及构造器，因此可以符合协议中的相应要求。详情请在扩展章节中查看。

注意

通过扩展令已有类型遵循并符合协议时，该类型的所有实例也会随之获得协议中定义的各项功能。

例如下面这个 TextRepresentable 协议，任何想要通过文本表示一些内容的类型都可以实现该协议。这些想要表示的内容可以是实例本身的描述，也可以是实例当前状态的文本描述：

protocol TextRepresentable {
    var textualDescription: String { get }
}
可以通过扩展，令先前提到的 Dice 类遵循并符合 TextRepresentable 协议：

extension Dice: TextRepresentable {
    var textualDescription: String {
        return "A \(sides)-sided dice"
    }
}
通过扩展遵循并符合协议，和在原始定义中遵循并符合协议的效果完全相同。协议名称写在类型名之后，以冒号隔开，然后在扩展的大括号内实现协议要求的内容。
*/

/*
有条件地遵循协议
泛型类型可能只在某些情况下满足一个协议的要求，比如当类型的泛型形式参数遵循对应协议时。你可以通过在扩展类型时列出限制让泛型类型有条件地遵循某协议。在你采纳协议的名字后面写泛型 where 分句。更多关于泛型 where 分句，见泛型 Where 分句。

下面的扩展让 Array 类型只要在存储遵循 TextRepresentable 协议的元素时就遵循 TextRepresentable 协议。

extension Array: TextRepresentable where Element: TextRepresentable {
    var textualDescription: String {
        let itemsAsText = self.map { $0.textualDescription }
        return "[" + itemsAsText.joined(separator: ", ") + "]"
    }
}
let myDice = [d6, d12]
print(myDice.textualDescription)
// 打印 "[A 6-sided dice, A 12-sided dice]"
*/

/*
在扩展里声明采纳协议
当一个类型已经符合了某个协议中的所有要求，却还没有声明采纳该协议时，可以通过空扩展体的扩展采纳该协议：

struct Hamster {
    var name: String
    var textualDescription: String {
        return "A hamster named \(name)"
    }
}
extension Hamster: TextRepresentable {}
*/

// --------------------------------------------------------------------

/*
协议扩展
协议可以通过扩展来为遵循协议的类型提供属性、方法以及下标的实现。通过这种方式，你可以基于协议本身来实现这些功能，而无需在每个遵循协议的类型中都重复同样的实现，也无需使用全局函数。

例如，可以扩展 RandomNumberGenerator 协议来提供 randomBool() 方法。该方法使用协议中定义的 random() 方法来返回一个随机的 Bool 值：
*/
extension RandomNumberGenerator {
    func randomBool() -> Bool {
        return random() > 0.5
    }
}
// 通过协议扩展，所有遵循协议的类型，都能自动获得这个扩展所增加的方法实现，无需任何额外修改：

let generator = LinearCongruentialGenerator()
print("Here's a random number: \(generator.random())")
// 打印 “Here's a random number: 0.37464991998171”
print("And here's a random Boolean: \(generator.randomBool())")
// 打印 “And here's a random Boolean: true”

/*
提供默认实现
可以通过协议扩展来为协议要求的属性、方法以及下标提供默认的实现。如果遵循协议的类型为这些要求提供了自己的实现，那么这些自定义实现将会替代扩展中的默认实现被使用。

注意

通过协议扩展为协议要求提供的默认实现和可选的协议要求不同。虽然在这两种情况下，遵循协议的类型都无需自己实现这些要求，但是通过扩展提供的默认实现可以直接调用，而无需使用可选链式调用。

例如，PrettyTextRepresentable 协议继承自 TextRepresentable 协议，可以为其提供一个默认的 prettyTextualDescription 属性，只是简单地返回 textualDescription 属性的值：
*/
extension PrettyTextRepresentable  {
    var prettyTextualDescription: String {
        return textualDescription
    }
}

/*
为协议扩展添加限制条件
在扩展协议的时候，可以指定一些限制条件，只有遵循协议的类型满足这些限制条件时，才能获得协议扩展提供的默认实现。这些限制条件写在协议名之后，使用 where 子句来描述，正如泛型 Where 子句中所描述的。

例如，你可以扩展 Collection 协议，适用于集合中的元素遵循了 Equatable 协议的情况。通过限制集合元素遵 Equatable 协议， 作为标准库的一部分， 你可以使用 == 和 != 操作符来检查两个元素的等价性和非等价性。
*/

extension Collection where Element: Equatable {
    func allEqual() -> Bool {
        for element in self {
            if element != self.first {
                return false
            }
        }
        return true
    }
}
// 如果集合中的所有元素都一致，allEqual() 方法才返回 true。

// 看看两个整数数组，一个数组的所有元素都是一样的，另一个不一样：

let equalNumbers = [100, 100, 100, 100, 100]
let differentNumbers = [100, 100, 200, 100, 200]
// 由于数组遵循 Collection 而且整数遵循 Equatable，equalNumbers 和 differentNumbers 都可以使用 allEqual() 方法。

print(equalNumbers.allEqual())
// 打印 "true"
print(differentNumbers.allEqual())
// 打印 "false"


