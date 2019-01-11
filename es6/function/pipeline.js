
//管道: 前一个函数的输出是最后一个函数的输入。
// node & chrome throw error 

const pipeline = (...funcs) => val => funcs.reduce((a,b) = > b(a), val);

const plus1 = a => a + 1;
const mult2 = a => a * 2;

const addThenMult = pipeline(plus1, mult2);

console.log(addThenMult(5));

