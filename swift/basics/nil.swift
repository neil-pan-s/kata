
/*

Swift 的 nil 和 Objective-C 中的 nil 并不一样。在 Objective-C 中，nil 是一个指向不存在对象的指针。在 Swift 中，nil 不是指针——它是一个确定的值，用来表示值缺失。任何类型的可选状态都可以被设置为 nil，不只是对象类型。

nil 不能用于非可选的常量和变量。如果你的代码中有常量或者变量需要处理值缺失的情况，请把它们声明成对应的可选类型。
*/

// 你可以给可选变量赋值为 nil 来表示它没有值：

var serverResponseCode: Int? = 404
// serverResponseCode 包含一个可选的 Int 值 404
serverResponseCode = nil
// serverResponseCode 现在不包含值


// 如果你声明一个可选常量或者变量但是没有赋值，它们会自动被设置为 nil：

var surveyAnswer: String?
// surveyAnswer 被自动设置为 nil

if (surveyAnswer == nil ) { 
	print("haha")
}

