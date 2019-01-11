

var obj = {
	*gen(){
		yield 1;
		yield 2;
		yield 3;
	}
};

var iterator = obj.gen();

console.log(iterator.next());
console.log(iterator.next());
console.log(iterator.next());

