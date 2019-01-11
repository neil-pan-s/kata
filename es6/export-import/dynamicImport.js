/**
 * 
 * import命令会被 JavaScript 引擎静态分析，先于模块内的其他模块执行（叫做”连接“更合适）
 * import和export命令只能在模块的顶层，不能在代码块之中（比如，在if代码块之中，或在函数之中）。
 * 
 * 引入 import()函数  
 * import函数的参数specifier，指定所要加载的模块的位置。import命令能够接受什么参数，import()函数就能接受什么参数，两者区别主要是后者为动态加载。
 * import()返回一个 Promise 对象
 * 
 * polyfill : systemjs
 */

//case 1 按需加载

button.addEventListener('click', event => {
    import ('./dialogBox.js')
    .then(dialogBox => {
            dialogBox.open();
        })
        .catch(error => {
            /* Error handling */
        })
});


//case 2 条件加载 
if (condition) {
    import ('moduleA').then(...);
} else {
    import ('moduleB').then(...);
}

//case 3 动态的模块路径
//根据函数f的返回结果，加载不同的模块。
import (f())
.then(...);



//case 4 模块解构
//import()加载模块成功以后，这个模块会作为一个对象，当作then方法的参数。因此，可以使用对象解构赋值的语法，获取输出接口。
import ('./myModule.js')
.then(({ export1, export2 }) => {
    // ...·
});

import ('./myModule.js')
.then(({ default: theDefault }) => {
    console.log(theDefault);
});