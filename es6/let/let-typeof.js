
// 暂时性死区(TDZ) - 在变量未声明前 使用该变量都会报错
// console.log(x);
// let x = 1;

//let 没有变量提升 所以typeof不再安全 可能会抛出错误
// try{
//     typeof y
// }catch(e){
//     console.log(e);
// }

// let y = 1;

//不允许重复定义变量 否则抛错
{
    let a = 1;
    let a = 2;
}

