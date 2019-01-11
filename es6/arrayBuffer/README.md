
## ArrayBuffer

二进制数组由三类对象组成。

（1）ArrayBuffer对象：代表内存之中的一段二进制数据，可以通过“视图”进行操作。“视图”部署了数组接口，这意味着，可以用数组的方法操作内存。

（2）TypedArray视图：共包括9种类型的视图，比如Uint8Array（无符号8位整数）数组视图, Int16Array（16位整数）数组视图, Float32Array（32位浮点数）数组视图等等。

（3）DataView视图：可以自定义复合格式的视图，比如第一个字节是Uint8（无符号8位整数）、第二、三个字节是Int16（16位整数）、第四个字节开始是Float32（32位浮点数）等等，此外还可以自定义字节序。

简单说，ArrayBuffer对象代表原始的二进制数据，TypedArray视图用来读写简单类型的二进制数据，DataView视图用来读写复杂类型的二进制数据。

TypedArray视图支持的数据类型一共有9种（DataView视图支持除Uint8C以外的其他8种）。

数据类型	字节长度	含义	对应的C语言类型
Int8	1	8位带符号整数	signed char
Uint8	1	8位不带符号整数	unsigned char
Uint8C	1	8位不带符号整数（自动过滤溢出）	unsigned char
Int16	2	16位带符号整数	short
Uint16	2	16位不带符号整数	unsigned short
Int32	4	32位带符号整数	int
Uint32	4	32位不带符号的整数	unsigned int
Float32	4	32位浮点数	float
Float64	8	64位浮点数	double

同一段内存，不同数据有不同的解读方式，这就叫做“视图”（view）。
ArrayBuffer有两种视图，一种是TypedArray视图，另一种是DataView视图。前者的数组成员都是同一个数据类型，后者的数组成员可以是不同的数据类型。

## TypedArray 

目前， TypedArray视图一共包括9种类型， 每一种视图都是一种构造函数。

Int8Array： 8 位有符号整数， 长度1个字节。
Uint8Array： 8 位无符号整数， 长度1个字节。
Uint8ClampedArray： 8 位无符号整数， 长度1个字节， 溢出处理不同。
Int16Array： 16 位有符号整数， 长度2个字节。
Uint16Array： 16 位无符号整数， 长度2个字节。
Int32Array： 32 位有符号整数， 长度4个字节。
Uint32Array： 32 位无符号整数， 长度4个字节。
Float32Array： 32 位浮点数， 长度4个字节。
Float64Array： 64 位浮点数， 长度8个字节。


## DataView

DataView视图提供更多操作选项，而且支持设定字节序。本来，在设计目的上，ArrayBuffer对象的各种TypedArray视图，是用来向网卡、声卡之类的本机设备传送数据，所以使用本机的字节序就可以了；而DataView视图的设计目的，是用来处理网络设备传来的数据，所以大端字节序或小端字节序是可以自行设定的。

DataView实例提供8个方法读取内存。

getInt8：读取1个字节，返回一个8位整数。
getUint8：读取1个字节，返回一个无符号的8位整数。
getInt16：读取2个字节，返回一个16位整数。
getUint16：读取2个字节，返回一个无符号的16位整数。
getInt32：读取4个字节，返回一个32位整数。
getUint32：读取4个字节，返回一个无符号的32位整数。
getFloat32：读取4个字节，返回一个32位浮点数。
getFloat64：读取8个字节，返回一个64位浮点数。
