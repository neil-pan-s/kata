

//只要某种数据结构有Iterator接口，就可采用数组形势解构赋值

//case 1
let [x,y,z] = new Set([1,2,3]);
console.log(x,y,z);

//case 2
function* fibs(){
	var a = 0;
	var b = 1;
	while(true){
		yield a;
		[a , b] = [b, a + b];
	}
}

var [first, second, third, fourth] = fibs();
console.log(first, second, third, fourth);
