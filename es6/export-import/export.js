//case 1 as关键字重命名
function v1() {}

function v2() {}

export {
    v1 as streamV1,
    v2 as streamV2,
    v2 as streamLatestVersion
};

//case 2 导出变量
//method 1
var firstName = 'Michael';
var lastName = 'Jackson';
var year = 1958;

export { firstName, lastName, year };

//method 2
export var firstName = 'Michael';
export var lastName = 'Jackson';
export var year = 1958;


//case 3 导出函数
export function f() {};

function f() {}
export { f };