

let {x} = {x:1};
console.log(x);

//equal to this:
let y;
({y} = {y:1});
console.log(y);


//case 1
{
	let { foo, bar } = { foo: "foo", bar : "bar"};
	console.log(foo,bar);
}

//case 2
{
	let { bar, foo } = { foo: "foo", bar : "bar"};
	console.log(foo,bar);
}

//case 3
{
	let { foo : x } = { foo: "foo", bar : "bar" };
	console.log(x);
}

//case 4
{
	let { p : [x, {y } ] } = {
		p: [
			"hello",
			{ y : "fish"}
		]
	};

	console.log(x,y);
}

