//case 1
var obj = new Proxy({}, {
    get: function(target, key, receiver) {
        console.log(`getting ${key}!`);
        return Reflect.get(target, key, receiver);
    },
    set: function(target, key, value, receiver) {
        console.log(`setting ${key}!`);
        return Reflect.set(target, key, value, receiver);
    }
});

obj.count = 1;
//  setting count!
++obj.count;
//  getting count!
//  setting count!
//  2


//case 2 proxy方法可以继承 拦截操作定义在Prototype对象上面，所以如果读取obj对象继承的属性时，拦截会生效。
let proto = new Proxy({}, {
    get(target, propertyKey, receiver) {
        console.log('GET ' + propertyKey);
        return target[propertyKey];
    }
});

var obj = Object.create(proto);
obj.xxx // "GET xxx"