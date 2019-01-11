
/*
布尔值
Swift 有一个基本的布尔（Boolean）类型，叫做 Bool。布尔值指逻辑上的值，因为它们只能是真或者假。Swift 有两个布尔常量，true 和 false：
*/


var isBest = true 

if isBest {
	print("Mmm")
} else {
	print("Eww")
}

/*
如果你在需要使用 Bool 类型的地方使用了非布尔值，Swift 的类型安全机制会报错。下面的例子会报告一个编译时错误：

let i = 1
if i {
    // 这个例子不会通过编译，会报错
}

*/

// 然而，下面的例子是合法的：
let i = 1
if i == 1 {
    // 这个例子会编译成功
}


// 三元表达式 
i == 1  ? print(1) : print(2) 


