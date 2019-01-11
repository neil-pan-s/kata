// case 1
const set = new Set([1, 2, 3, 4, 4]);

console.log([...set])
    // [1, 2, 3, 4]

for (let i of set) {
    console.log(i);
}
//1 2 3 4 

// case 2
const items = new Set([1, 2, 3, 4, 5, 5, 5, 5]);
console.log(items.size) // 5

//case 3 NAN and {}
{
    //在 Set 内部，两个NaN是相等。
    let set = new Set();
    let a = NaN;
    let b = NaN;
    set.add(a);
    set.add(b);
    console.log(set) // Set {NaN}
}

{
    //由于两个空对象不相等，所以它们被视为两个值。
    let set = new Set();

    set.add({});
    console.log(set.size) // 1

    set.add({});
    console.log(set.size) // 2 
}

//case 4
{
    let s = new Set();

    s.add(1).add(2).add(2);
    // 注意2被加入了两次

    s.size // 2

    s.has(1) // true
    s.has(2) // true
    s.has(3) // false

    s.delete(2);
    s.has(2) // false

    s.clear();
    s.size
}