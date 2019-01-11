
//标签模板是一种特殊的函数调用形式， 标签是指函数，紧跟在后面的字符串是其参数。
//该函数 第一个参数为字符串模板中以没有变量替换的部分，第一个参数为数组，后续枚举参数为模板变量

function i18n(templateData, var1, var2, var3){
	
	let s = "";

	(templateData[0] === 'hello ') && (s += "你好");
	(var1 === 'fish') && (s += '新手');
	
	return s;
}

let name = "fish";
let s = i18n`hello ${name}`;

console.log(s);
