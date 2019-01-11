
/*
协议的继承
协议能够继承一个或多个其他协议，可以在继承的协议的基础上增加新的要求。协议的继承语法与类的继承相似，多个被继承的协议间用逗号分隔：

protocol InheritingProtocol: SomeProtocol, AnotherProtocol {
    // 这里是协议的定义部分
}
如下所示，PrettyTextRepresentable 协议继承了 TextRepresentable 协议：

protocol PrettyTextRepresentable: TextRepresentable {
    var prettyTextualDescription: String { get }
}
*/


