
/*
可选的协议要求
协议可以定义可选要求，遵循协议的类型可以选择是否实现这些要求。在协议中使用 optional 关键字作为前缀来定义可选要求。可选要求用在你需要和 Objective-C 打交道的代码中。协议和可选要求都必须带上 @objc 属性。标记 @objc 特性的协议只能被继承自 Objective-C 类的类或者 @objc 类遵循，其他类以及结构体和枚举均不能遵循这种协议。

协议中的可选要求可通过可选链式调用来使用，因为遵循协议的类型可能没有实现这些可选要求。类似 someOptionalMethod?(someArgument) 这样，你可以在可选方法名称后加上 ? 来调用可选方法。
*/

// 下面的例子定义了一个名为 Counter 的用于整数计数的类，它使用外部的数据源来提供每次的增量。数据源由 CounterDataSource 协议定义，包含两个可选要求：

import Foundation

@objc protocol CounterDataSource {
    @objc optional func incrementForCount(_ count: Int) -> Int
    @objc optional var fixedIncrement: Int { get }
}


class Counter {
    var count = 0
    var dataSource: CounterDataSource?
    func increment() {
        if let amount = dataSource?.incrementForCount?(count) {
            count += amount
        } else if let amount = dataSource?.fixedIncrement {
            count += amount
        }
    }
}

class ThreeSource: NSObject, CounterDataSource {
    let fixedIncrement = 3
}

var counter = Counter()
counter.dataSource = ThreeSource()
for _ in 1...4 {
    counter.increment()
    print(counter.count)
}
// 3
// 6
// 9
// 12
