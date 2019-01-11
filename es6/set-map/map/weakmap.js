const wm = new WeakMap();
let key = {};
let obj = { foo: 1 };

//WeakMap 弱引用的只是键名，而不是键值。键值依然是正常引用。
wm.set(key, obj);
obj.foo = 2;
obj = null;
wm.get(key);
// Object {foo: 2}