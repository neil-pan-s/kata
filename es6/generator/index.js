
/**
 * yield关键字使生成器函数执行暂停，yield关键字后面的表达式的值返回给生成器的调用者。它可以被认为是一个基于生成器的版本的return关键字。
 */

//Case 1
function func1() {
    console.log("func1");
}

function func2() {
    console.log("func2");
}

function func3() {
    console.log("func3");
}

function* yieldTest() {
    yield func1
    yield func2
    yield func3
}

var iterator = yieldTest();
console.log(iterator.next().value());
console.log(iterator.next());
console.log(iterator.next());
console.log(iterator.next());

//Case 2
function* foo() {
    var index = 0;
    while (index <= 2)
    // when index reaches 3, 
    // yield's done will be true 
    // and its value will be undefined;
        yield index++;
}

//一旦生成器函数已定义，可以通过构造一个迭代器来使用它.
var iterator = foo();
console.log(iterator.next());
// { value:0, done:false }
console.log(iterator.next());
// { value:1, done:false }
console.log(iterator.next());
// { value:2, done:false }
console.log(iterator.next());
// { value:undefined, done:true }


//case 3
function* demo() {

    function foo(a, b) {
        console.log("hahahahahahaha");
    }

    foo(yield 'a', yield 'b'); // OK
    let input = yield; // OK
    console.log("input = " + input);
}

var ite = demo();

ite.next(1); //{ value: 'a', done: false }
ite.next(2); //{ value: 'b', done: false }
ite.next(3); //hahahahahahaha { value: undefined, done: false }
ite.next(4); //input = 4 { value: undefined, done: false }

//case 4
function* demo() {
    console.log('Hello ' + (yield)); // OK
    console.log('Hello ' + (yield 123)); // OK
}

var ite = demo();

//由于next方法的参数表示上一个yield表达式的返回值，所以第一次使用next方法时，不能带有参数。
//V8 引擎直接忽略第一次使用next方法时的参数，只有从第二次使用next方法开始，参数才是有效的。
//从语义上讲，第一个next方法用来启动遍历器对象，所以不用带有参数。
ite.next('A'); //{ value: undefined, done: false }
ite.next('B'); //{ value: 123, done: false } Hello A
ite.next('C'); //Hello B { value: undefined, done: true }