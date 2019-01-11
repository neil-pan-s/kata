
/*
下标允许你通过在实例名称后面的方括号中传入一个或者多个索引值来对实例进行存取。语法类似于实例方法语法和计算型属性语法的混合。与定义实例方法类似，定义下标使用 subscript 关键字，指定一个或多个输入参数和返回类型；与实例方法不同的是，下标可以设定为读写或只读。这种行为由 getter 和 setter 实现，有点类似计算型属性：

subscript(index: Int) -> Int {
    get {
      // 返回一个适当的 Int 类型的值
    }

    set(newValue) {
      // 执行适当的赋值操作
    }
}
newValue 的类型和下标的返回类型相同。如同计算型属性，可以不指定 setter 的参数（newValue）。如果不指定参数，setter 会提供一个名为 newValue 的默认参数。

如同只读计算型属性，可以省略只读下标的 get 关键字：

subscript(index: Int) -> Int {
    // 返回一个适当的 Int 类型的值
}

*/

// 下面代码演示了只读下标的实现，这里定义了一个 TimesTable 结构体，用来表示传入整数的乘法表：

struct TimesTable {
    let multiplier: Int
    subscript(index: Int) -> Int {
        return multiplier * index
    }
}
let threeTimesTable = TimesTable(multiplier: 3)
print("six times three is \(threeTimesTable[6])")
// 打印 "six times three is 18"
*/

/* 
下标选项
下标可以接受任意数量的入参，并且这些入参可以是任意类型。下标的返回值也可以是任意类型。下标可以使用变量参数和可变参数，但不能使用输入输出参数，也不能给参数设置默认值。

一个类或结构体可以根据自身需要提供多个下标实现，使用下标时将通过入参的数量和类型进行区分，自动匹配合适的下标，这就是下标的重载。
*/

// 虽然接受单一入参的下标是最常见的，但也可以根据情况定义接受多个入参的下标。例如下例定义了一个 Matrix 结构体，用于表示一个 Double 类型的二维矩阵。Matrix 结构体的下标接受两个整型参数：

struct Matrix {
    let rows: Int, columns: Int
    var grid: [Double]
    init(rows: Int, columns: Int) {
        self.rows = rows
        self.columns = columns
        grid = Array(repeating: 0.0, count: rows * columns)
    }
    func indexIsValid(row: Int, column: Int) -> Bool {
        return row >= 0 && row < rows && column >= 0 && column < columns
    }
    subscript(row: Int, column: Int) -> Double {
        get {
            assert(indexIsValid(row: row, column: column), "Index out of range")
            return grid[(row * columns) + column]
        }
        set {
            assert(indexIsValid(row: row, column: column), "Index out of range")
            grid[(row * columns) + column] = newValue
        }
    }
}
// Matrix 提供了一个接受两个入参的构造方法，入参分别是 rows 和 columns，创建了一个足够容纳 rows * columns 个 Double 类型的值的数组。通过传入数组长度和初始值 0.0 到数组的构造器，将矩阵中每个位置的值初始化为 0.0。关于数组的这种构造方法请参考创建一个带有默认值的数组。

// 你可以通过传入合适的 row 和 column 的数量来构造一个新的 Matrix 实例：

var matrix = Matrix(rows: 2, columns: 2)
// 上例中创建了一个 Matrix 实例来表示两行两列的矩阵。该 Matrix 实例的 grid 数组按照从左上到右下的阅读顺序将矩阵扁平化存储：



// 将 row 和 column 的值传入下标来为矩阵设值，下标的入参使用逗号分隔：

matrix[0, 1] = 1.5
matrix[1, 0] = 3.2
