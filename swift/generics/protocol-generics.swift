
/*
关联类型
定义一个协议时，有的时候声明一个或多个关联类型作为协议定义的一部分将会非常有用。关联类型为协议中的某个类型提供了一个占位名（或者说别名），其代表的实际类型在协议被采纳时才会被指定。你可以通过 associatedtype 关键字来指定关联类型。

*/

// 关联类型实践
// 下面例子定义了一个 Container 协议，该协议定义了一个关联类型 Item：

protocol Container {
    associatedtype Item
    mutating func append(_ item: Item)
    var count: Int { get }
    subscript(i: Int) -> Item { get }
}

// Container 协议声明了一个关联类型 Item，写作 associatedtype Item。这个协议无法定义 Item 是什么类型的别名，这个信息将留给遵从协议的类型来提供。

// 下面是先前的非泛型的 IntStack 类型，这一版本采纳并符合了 Container 协议：

struct IntStack: Container {
    // IntStack 的原始实现部分
    var items = [Int]()
    mutating func push(_ item: Int) {
        items.append(item)
    }
    mutating func pop() -> Int {
        return items.removeLast()
    }
    // Container 协议的实现部分
    typealias Item = Int
    mutating func append(_ item: Int) {
        self.push(item)
    }
    var count: Int {
        return items.count
    }
    subscript(i: Int) -> Int {
        return items[i]
    }
}


// 你也可以让泛型 Stack 结构体遵从 Container 协议：

struct Stack<Element>: Container {
    // Stack<Element> 的原始实现部分
    var items = [Element]()
    mutating func push(_ item: Element) {
        items.append(item)
    }
    mutating func pop() -> Element {
        return items.removeLast()
    }
    // Container 协议的实现部分
    mutating func append(_ item: Element) {
        self.push(item)
    }
    var count: Int {
        return items.count
    }
    subscript(i: Int) -> Element {
        return items[i]
    }
}
// 这一次，占位类型参数 Element 被用作 append(_:) 方法的 item 参数和下标的返回类型。Swift 可以据此推断出 Element 的类型即是 Item 的类型。

