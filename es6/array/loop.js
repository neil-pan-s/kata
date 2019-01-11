
//case 1
for(let index of ['a','b'].keys()){
	console.log(index);
}

//node & chrome unsupported 
//for(let elem of ['a','b'].values()){
//	console.log(elem);
//}

//case 2
for(let [index , elem] of ['a','b'].entries()){
	console.log(index , elem);
}

//case 3
var arr = ['w', 'y', 'k', 'o', 'p'];
var iterator = arr.entries();

for (let letter of iterator) {

	  console.log(letter);
}

//case 4
//for in 遍历的是数组的索引, 适合于遍历对象的课美剧属性 包括method
for (let index in ['a', 'b']){
	console.log(index)
}

//for of 遍历的是数组的元素值
for (let index of ['a', 'b']){
	console.log(index)
}
