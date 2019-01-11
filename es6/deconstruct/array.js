
//case 1
{
	let [x , y = 'b'] = ['a'];
	console.log(x,y);
}

//case 2
{
	let [x , y = 'b'] = ['a', null];
	console.log(x,y);
}

//case 3
{
	let [x , [y], z] = ['a', [1,2], 'c'];
	console.log(x,y,z);
}

//case 4
{
	let [,,z] = [1,2,3];
	console.log(z);
}

//case 5
{
	let [x,...y] = [1,2,3];
	console.log(x,y);
}


