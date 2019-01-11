
/*
类专属的协议
你通过添加 AnyObject 关键字到协议的继承列表，就可以限制协议只能被类类型采纳（以及非结构体或者非枚举的类型）。

protocol SomeClassOnlyProtocol: class, SomeInheritedProtocol {
    // 这里是类专属协议的定义部分
}
在以上例子中，协议 SomeClassOnlyProtocol 只能被类类型采纳。如果尝试让结构体或枚举类型采纳 SomeClassOnlyProtocol，则会导致编译时错误。

注意

当协议定义的要求需要遵循协议的类型必须是引用语义而非值语义时，应该采用类类型专属协议。关于引用语义和值语义的更多内容，请查看结构体和枚举是值类型和类是引用类型。
*/



