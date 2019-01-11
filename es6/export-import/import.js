//case 1
//支持相对路径和绝对路径
import { lastName } from './profile.js';
//.js 可以省略 
import { lastName } from './profile';
//如果只是模块名，不带有路径，那么必须有配置文件，告诉 JavaScript 引擎该模块的位置。
import { lastName } from 'profile';

/*
    import './foo';
    // 依次寻找
    //   ./foo.js
    //   ./foo/package.json
    //   ./foo/index.js

    import 'baz';
    // 依次寻找
    //   ./node_modules/baz.js
    //   ./node_modules/baz/package.json
    //   ./node_modules/baz/index.js
    // 寻找上一级目录
    //   ../node_modules/baz.js
    //   ../node_modules/baz/package.json
    //   ../node_modules/baz/index.js
    // 再上一级目录
*/

//case 2
//导出部分方法
import { area, circumference } from './profile';
//导出方法重命名
import { area as f1, circumference as f2 } from './profile';
//导出整个对象
import * as profile from './profile';

//case 3
//由于import是静态执行，所以不能使用表达式和变量，这些只有在运行时才能得到结果的语法结构。
// 报错
import { 'f' + 'oo' } from 'my_module';

// 报错
let module = 'my_module';
import { foo } from module;


//case 4 export default 
// 第一组
export default function crc32() { // 输出
    // ...
}

import crc32 from 'crc32'; // 输入

// 第二组
export function crc32() { // 输出
    // ...
};

import { crc32 } from 'crc32'; // 输入

// export default就是输出一个叫做default的变量或方法，然后系统允许你为它取任意名字
// modules.js
function add(x, y) {
    return x * y;
}
export { add as default };
// 等同于
// export default add;

// app.js
import { default as xxx } from 'modules';
// 等同于
// import xxx from 'modules';

//特殊例子
// 正确
var a = 1;
export default a;

// 正确
export default 42;

//如果想在一条import语句中，同时输入默认方法和其他变量，可以写成下面这样。
import _, { each } from 'lodash';


//case 5 export 与 import 的复合写法
//case 5.1 
export { foo, bar }
from 'my_module';

// 等同于
import { foo, bar } from 'my_module';
export { foo, bar };

//case 5.2
export { es6 as default }
from './someModule';

// 等同于
import { es6 } from './someModule';
export default es6;