//case 1 设置跨模块的常量（即跨多个文件），或者说一个值要被多个模块共享

// constants.js 模块
export const A = 1;
export const B = 3;
export const C = 4;

// test1.js 模块
import * as constants from './constants';
console.log(constants.A); // 1
console.log(constants.B); // 3

// test2.js 模块
import { A, B } from './constants';
console.log(A); // 1
console.log(B); // 3