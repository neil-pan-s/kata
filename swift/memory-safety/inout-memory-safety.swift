
/*
n-Out 参数的访问冲突
一个函数会对它所有的 in-out 参数进行长期写访问。in-out 参数的写访问会在所有非 in-out 参数处理完之后开始，直到函数执行完毕为止。如果有多个 in-out 参数，则写访问开始的顺序与参数的顺序一致。

长期访问的存在会造成一个结果，你不能在原变量以 in-out 形式传入后访问原变量，即使作用域原则和访问权限允许 —— 任何访问原变量的行为都会造成冲突。例如：

var stepSize = 1

func increment(_ number: inout Int) {
    number += stepSize
}

increment(&stepSize)
// 错误：stepSize 访问冲突
在上面的代码里，stepSize 是一个全局变量，并且它可以在 increment(_:) 里正常访问。然而，对于 stepSize 的读访问与 number 的写访问重叠了。就像下面展示的那样，number 和 stepSize 都指向了同一个存储地址。同一块内存的读和写访问重叠了，就此产生了冲突。



解决这个冲突的一种方式，是复制一份 stepSize 的副本：

// 复制一份副本
var copyOfStepSize = stepSize
increment(&copyOfStepSize)

// 更新原来的值
stepSize = copyOfStepSize
// stepSize 现在的值是 2
当你在调用 increment(_:) 之前复制一份副本，显然 copyOfStepSize 就会根据当前的 stepSize 增加。读访问在写操作之前就已经结束了，所以不会有冲突。

长期写访问的存在还会造成另一种结果，往同一个函数的多个 in-out 参数里传入同一个变量也会产生冲突，例如：

func balance(_ x: inout Int, _ y: inout Int) {
    let sum = x + y
    x = sum / 2
    y = sum - x
}
var playerOneScore = 42
var playerTwoScore = 30
balance(&playerOneScore, &playerTwoScore)  // 正常
balance(&playerOneScore, &playerOneScore)
// 错误：playerOneScore 访问冲突
上面的 balance(_:_:) 函数会将传入的两个参数平均化。将 playerOneScore 和 playerTwoScore 作为参数传入不会产生错误 —— 有两个访问重叠了，但它们访问的是不同的内存位置。相反，将 playerOneScore 作为参数同时传入就会产生冲突，因为它会发起两个写访问，同时访问同一个的存储地址。
*/

