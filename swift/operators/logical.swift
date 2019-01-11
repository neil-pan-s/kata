
/*
Swift 逻辑操作符 && 和 || 是左结合的，这意味着拥有多元逻辑操作符的复合表达式优先计算最左边的子表达式。
*/

// if enteredDoorCode && passedRetinaScan || hasDoorKey || knowsOverridePassword
if true && false || true || false {
    print("Welcome!")
} else {
    print("ACCESS DENIED")
}
// 输出 "Welcome!"
