
/* 检测 API 可用性
Swift 内置支持检查 API 可用性，这可以确保我们不会在当前部署机器上，不小心地使用了不可用的 API。

编译器使用 SDK 中的可用信息来验证我们的代码中使用的所有 API 在项目指定的部署目标上是否可用。如果我们尝试使用一个不可用的 API，Swift 会在编译时报错。

我们在 if 或 guard 语句中使用 可用性条件（availability condition)去有条件的执行一段代码，来在运行时判断调用的 API 是否可用。编译器使用从可用性条件语句中获取的信息去验证，在这个代码块中调用的 API 是否可用。

if #available(iOS 10, macOS 10.12, *) {
    // 在 iOS 使用 iOS 10 的 API, 在 macOS 使用 macOS 10.12 的 API
} else {
    // 使用先前版本的 iOS 和 macOS 的 API
}
以上可用性条件指定，if 语句的代码块仅仅在 iOS 10 或 macOS 10.12 及更高版本才运行。最后一个参数，*，是必须的，用于指定在所有其它平台中，如果版本号高于你的设备指定的最低版本，if 语句的代码块将会运行。

在它一般的形式中，可用性条件使用了一个平台名字和版本的列表。平台名字可以是 iOS，macOS，watchOS 和 tvOS——请访问声明属性来获取完整列表。除了指定像 iOS 8 或 macOS 10.10 的大版本号，也可以指定像 iOS 11.2.6 以及 macOS 10.13.3 的小版本号。

if #available(platform name version, ..., *) {
    APIs 可用，语句将执行
} else {
    APIs 不可用，语句将不执行
}
*/
