//case 1 chrome succ
function sleep(timeout) {
    return new Promise((resolve, reject) => {
        setTimeout(function() {
            resolve("Hello Block Api");
        }, timeout);
    });
}

async function blockTest() {
    console.log('Do some thing, ' + new Date());
    var s = await sleep(3000);
    console.log('Do other things, ' + new Date());
    return s;
}

(async function() {
    while (1) {
        var s = await blockTest();
        alert(s);
    }
})();

//case 2
async function f() {
    await Promise.reject('404 error');
}

f()
    .then(v => console.log(v))
    .catch(e => console.log(e))
    // 404 error

//case 3
//await命令后面的Promise对象，运行结果可能是rejected，所以最好把await命令放在try...catch代码块中
async function f() {
    await Promise.reject('404 error');
    await Promise.resolve('hello world'); // 不会执行
}

async function f() {
    try {
        await Promise.reject('404 error');
    } catch (error) {

    }
    await Promise.resolve('hello world'); // 不会执行
}