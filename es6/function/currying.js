
//柯里化: 将多参数的函数转化为单参数的函数

//case 1
function add(x,y){
	return x + y;
}

function curryingAdd(x){
	return function(y){
		return x + y;
	}
}

console.log(curryingAdd(1)(2));
console.log(curryingAdd(2)(3));

//case 2
function currying(fn, n){
	return function(m){
		return fn.call(this,m,n);
	}
}

function add(x, y){
	return x + y;
}

let add1 = currying(add, 1);
console.log(add1(2));

let add2 = currying(add, 2);
console.log(add2(2));


