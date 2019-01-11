// WeakSet 没有size属性 不能遍历 没有forEach方法

const ws = new WeakSet();
const obj = {};
const foo = {};

ws.add(foo);
ws.add(obj);

ws.has(foo); // true
ws.has(obj); // true

ws.delete(obj);
ws.has(obj); // false