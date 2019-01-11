

// case 1
function factorial(n){
	if(n === 1) return 1;
	return n * factorial(n - 1);
}

console.log(new Date());
factorial(5);
console.log(new Date());

//case 2
function factorial(n, total = 1){
	if(n === 1) return total;
	return factorial(n -1 , n * total);
}

console.log(new Date());
factorial(5);
console.log(new Date());
