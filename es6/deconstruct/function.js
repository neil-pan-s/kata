
function add([x,y]){
	return x+y;
}

console.log(add([1,2,3]));

//case 1
function move({x,y}){
	return [x,y];
}

console.log(move({x:1,y:2,z:3}));

//case 2
//为第一个参数制定默认值
function move({x,y} = { x:0, y: 0}){
	return [x,y];
}

console.log(move({x:1,y:2,z:3}));
//有空参数 对象结构为undefined
console.log(move({}));
//无参数
console.log(move());

//case 3
//指定解构默认值, node throw error, chrome ok
//function move({x = 0 , y = 0}){
//	return [x,y];
//}

//console.log(move({x:1,y:2,z:3}));
//有空参数 对象结构为undefined
//console.log(move({}));

//case 4 
//指定解构默认值＋参数默认值
function move({x = 0 , y = 0} = {}){
	return [x,y];
}

console.log(move({x:1,y:2,z:3}));
//有空参数 对象结构为undefined, node throw error, chrome ok 
console.log(move({}));

