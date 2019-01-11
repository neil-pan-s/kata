//Case 0 Promise 基础使用
// var p = new Promise(function(resolve,reject){
//     console.log("Hello Promise Start");
//     //do sth. async action
//     setTimeout(function(){
//         console.log("Timeout");

//         //case 0.1 正常resolve 
//         resolve();
//         //case 0.2 异常reject
//         //reject();
//         //case 0.3 带返回值resolve
//         //resolve(":)");

//     },1000);
//     console.log("Hello Promise End");
// });

// console.log("~Mark");
// p.then(function(s){
//     console.log("ok, It's Timeout! " + s);
// });

// p.catch(function(e){
//     console.log("ok, It's Wrong! " + e);
// });

//Case 1 Promise 执行顺序理解
// var p0 = Promise.resolve();
// p0.then(function(){
//     console.log("Step 0");   
// }).then(function(){
//     console.log("Step 1");   
// });

// p0.then(function(){
//     console.log("Step 2");   
// }).then(function(){
//     console.log("Step 3");   
// })


//Case 2 理解 Promise 链式语法 then返回值
// var p1 = Promise.resolve();
// var p2 = p1.then(function() {
//     console.log("Hello World");
// });
// console.log("P2:");
// console.log(p2);
// console.log(p2 != p1);


//Case 3 理解 Promise then函数的返回值
// var p3 = Promise.resolve();
// p3.then(function(s) {
//     console.log("ok, First Then! " + s);
//     return 1;
// }).then(function(s) {
//     console.log("ok, Second Then! " + s);
//     return { s: "Hello World" };
// }).then(function(s) {
//     console.log("ok, Third Then! " + JSON.stringify(s));
//     return new Promise(function(resolve, reject) {
//         setTimeout(function() {
//             resolve(1);
//         }, 100);
//     });
// }).then(function(s) {
//     console.log("ok, Forth Then! " + s);
// });

//Case 4 异步嵌套和Promise的比较
// function func1(succfn, failfn) {
//     setTimeout(function() {
//         console.log("ok, First Function! ");
//         succfn();
//     }, 2000);
// }

// function func2(succfn, failfn) {
//     setTimeout(function() {
//         console.log("ok, Second Function! ");
//         succfn();
//     }, 1000);
// }

// function func3(succfn, failfn) {
//     setTimeout(function() {
//         console.log("ok, Third Function! ");
//         succfn();
//     }, 1500);
// }

// func1(function(){
//     func2(function(){
//         func3(function(){

//         },function(){
//             console.log("sth. wrong");
//         });   
//     },function(){
//         console.log("sth. wrong");
//     });
// },function(){
//     console.log("sth. wrong");
// });


// Promise.resolve()
//     .then(function() {
//         var p = new Promise(function(resolve, reject) {
//             func1(function() {
//                 resolve(1);
//             }, function() {
//                 console.log("sth. wrong");
//                 reject();
//             });
//         });
//         console.log("Notice return execute immediately");
//         //return is nessary
//         return p;
//     })
//     .then(function(x) {
//         console.log("Notice return not Promise Object,It's resolve args");
//         console.log(x);
//         return new Promise(function(resolve, reject) {
//             func2(function() {
//                 resolve(2);
//             }, function() {
//                 console.log("sth. wrong");
//                 reject();
//             });
//         });
//     })
//     .then(function() {
//         return new Promise(function(resolve, reject) {
//             func3(function() {
//                 resolve(3);
//             }, function() {
//                 console.log("sth. wrong");
//                 reject();
//             });
//         });
//     });

//Case x Promise.all/Promise.race
// function func1(succfn,failfn){
//     setTimeout(function(){
//         console.log("ok, First Function! ");
//         succfn();
//     },2000);    
// }

// function func2(succfn,failfn){
//     setTimeout(function(){
//         console.log("ok, Second Function! ");
//         succfn();
//     },1000);    
// }

// function func3(succfn,failfn){
//     setTimeout(function(){
//         console.log("ok, Third Function! ");
//         succfn();
//     },1500);    
// }

// var p1 = function(){
//     return new Promise(function(resolve,reject){
//         func1(function(){
//             resolve(1);
//         });
//     });
// }

// var p2 = function(){
//     new Promise(function(resolve,reject){
//         func2(function(){
//             resolve(2);
//         });
//     });
// }

// var p3 = function(){
//     new Promise(function(resolve,reject){
//         func3(function(){
//             resolve(3);
//         });
//     });
// }

//并发同时执行,非前后顺序依次执行，全部执行完后才resolve
// Promise.all([p1(),p2(),p3()]).then(function(){
//     console.log("Promise All Completed");
// });
//并发同时执行,非前后顺序依次执行，有单个执行完后就resolve [此处存在问题]
// Promise.race([p1(),p2(),p3()]).then(function(x){
//     console.log("Promise Race Completed " + x);
// });