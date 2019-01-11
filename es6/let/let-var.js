
// let 仅在当前代码块内有效 不存在变量提升问题

// {
//     let a = 10;
//     var b = 1;
// }

// console.log(b) // 1 
// console.log(a) // not defined 

// let 声明不会添加到全局属性

var x = 1;
console.log(window.x);

let y = 1;
console.log(window.y);

