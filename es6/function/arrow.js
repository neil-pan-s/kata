
//case 1
var fn = v => console.log(v);
fn(9527);

//case 2 无参数
var fn2 = () => console.log('hi fish');
fn2();

//case 3 多参数
var fn3 = (a,b,c) => console.log(a,b,c);
fn3(1,2,3);

//case 4 多语句
var fn4 = (x ,y) => {
	let a = x + y;
	return a * 2;
};
console.log(fn4(1,2));


//case 5 return obj 
var fn5 = () => ({ a: 1, b: 2});
console.log(fn5());


//case 6 this

var foo = {
	name: "apple",
	bar: () => console.log(this.name),
	bar_: function(){
		(() => console.log(this.name))();
	},
	bar__: () => {
		//f**k 谜之this啊 node & chrome 不一致
		console.log(this);
	},
	bar___(){
		console.log(this.name);
	}
};

foo.bar(); //undifined
foo.bar_(); //apple
foo.bar__();// {}
foo.bar___(); // apple

//case 7 setTimeout this
var foo = {
	name: "apple",
	bar: function(){
		setTimeout(()=>{
			console.log(this.name);
			console.log(this === global);
		},100);
	}
};

foo.bar();
foo.bar.call({name: "orange"});
