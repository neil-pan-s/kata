
/* Swift Basic Variable Type: Int Double Float String Bool */


/*
一般来说你很少需要写类型标注。如果你在声明常量或者变量的时候赋了一个初始值，Swift 可以推断出这个常量或者变量的类型，请参考类型安全和类型推断
*/

var x = 0.0, y = 0.0, z = 0.0
print(x,y,z)

// 类型标注
var welcomeMessage: String, blue: Double  // init with "" is better 
welcomeMessage = "hello world"  // must use "" not ''
 
