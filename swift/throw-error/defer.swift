
/*
指定清理操作
你可以使用 defer 语句在即将离开当前代码块时执行一系列语句。该语句让你能执行一些必要的清理工作，不管是以何种方式离开当前代码块的——无论是由于抛出错误而离开，或是由于诸如 return、break 的语句。例如，你可以用 defer 语句来确保文件描述符得以关闭，以及手动分配的内存得以释放。

defer 语句将代码的执行延迟到当前的作用域退出之前。该语句由 defer 关键字和要被延迟执行的语句组成。延迟执行的语句不能包含任何控制转移语句，例如 break、return 语句，或是抛出一个错误。延迟执行的操作会按照它们声明的顺序从后往前执行——也就是说，第一条 defer 语句中的代码最后才执行，第二条 defer 语句中的代码倒数第二个执行，以此类推。最后一条语句会第一个执行。

func processFile(filename: String) throws {
    if exists(filename) {
        let file = open(filename)
        defer {
            close(file)
        }
        while let line = try file.readline() {
            // 处理文件。
        }
        // close(file) 会在这里被调用，即作用域的最后。
    }
}
*/
