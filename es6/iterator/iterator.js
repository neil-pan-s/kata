//遍历器对象除了具有next方法，还可以具有return方法和throw方法。如果你自己写遍历器对象生成函数，那么next方法是必须部署的，return方法和throw方法是否部署是可选的。
//return方法的使用场合是， 如果for...of循环提前退出（ 通常是因为出错， 或者有break语句或continue语句）， 就会调用return方法。 如果一个对象在完成遍历前， 需要清理或释放资源， 就可以部署return方法。

var obj = {
    [Symbol.iterator]() {

        var tmp = [1, 2, 3, 4, 5];
        var index = 0;

        return {
            next() {
                return (index < tmp.length) ? { value: tmp[index++], done: false } : { done: true };
            },
            return () {
                console.log("it's end");
                return { done: true };
            },
        };
    }
}

for (let line of obj) {
    console.log(line);
    break;
}