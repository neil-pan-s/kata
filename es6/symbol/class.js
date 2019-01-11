//case 1 Symbol.hasInstance
{
    class MyClass {
        static[Symbol.hasInstance](x) {
            return Number(x) % 2 === 0;
        }
    }

    console.log(1 instanceof MyClass) // false
    console.log(2 instanceof MyClass) // true

    var obj = {
        [Symbol.hasInstance](x) {
            return Number(x) % 2 === 0;
        }
    };
    console.log(1 instanceof obj) // false
    console.log(2 instanceof obj) // true
}

//case 2 Symbol.iterator
{
    var obj = {
        [Symbol.iterator]: function*() {
            yield 1;
            yield 2;
            yield 3;
        }
    }

    console.log([...obj]) // [1, 2, 3]
    for (let value of obj) {
        console.log(value);
    }
    // 1
    // 2
    // 3
}

//case 3 Symbol.toPrimitive
{
    let obj = {
        [Symbol.toPrimitive](hint) {
            switch (hint) {
                case 'number':
                    return 123;
                case 'string':
                    return 'str';
                case 'default':
                    return 'default';
                default:
                    throw new Error();
            }
        }
    };

    console.log(2 * obj) // 246
    console.log(3 + obj) // '3default'
    console.log(obj == 'default') // true
    console.log(String(obj)) // 'str'
}

//case 4  Symbol.toStringTag
{
    let obj = {
        [Symbol.toStringTag]: 'Foo'
    };
    console.log(obj.toString()); // "[object Foo]"
}