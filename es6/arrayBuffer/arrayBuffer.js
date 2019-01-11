/**
 * ArrayBuffer对象代表储存二进制数据的一段内存， 它不能直接读写， 只能通过视图（ TypedArray视图和DataView视图) 来读写， 视图的作用是以指定格式解读二进制数据。
 * ArrayBuffer也是一个构造函数， 可以分配一段可以存放数据的连续内存区域。
 */

//上面代码生成了一段32字节的内存区域，每个字节的值默认都是0。
var buf = new ArrayBuffer(32);

//建立DataView视图，然后以不带符号的8位整数格式，读取第一个元素，结果得到0
var dataView = new DataView(buf);
dataView.getUint8(0) // 0


//对同一段内存，分别建立两种视图：32位带符号整数（Int32Array构造函数）和8位不带符号整数（Uint8Array构造函数）
var x1 = new Uint8Array(buf);
x1[0] = 2;
var x2 = new Int32Array(buf);
x2[0] //2