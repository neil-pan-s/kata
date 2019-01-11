

let [a,b] = "hello";
console.log(a,b);

// 等号右边非对象，则优先转换为原型对象
let {length : len} = "hello";
console.log(len);

