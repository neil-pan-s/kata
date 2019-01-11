
/*
带标签的语句
在 Swift 中，你可以在循环体和条件语句中嵌套循环体和条件语句来创造复杂的控制流结构。并且，循环体和条件语句都可以使用 break 语句来提前结束整个代码块。因此，显式地指明 break 语句想要终止的是哪个循环体或者条件语句，会很有用。类似地，如果你有许多嵌套的循环体，显式指明 continue 语句想要影响哪一个循环体也会非常有用。

为了实现这个目的，你可以使用标签（statement label）来标记一个循环体或者条件语句，对于一个条件语句，你可以使用 break 加标签的方式，来结束这个被标记的语句。对于一个循环语句，你可以使用 break 或者 continue 加标签，来结束或者继续这条被标记语句的执行。

声明一个带标签的语句是通过在该语句的关键词的同一行前面放置一个标签，作为这个语句的前导关键字（introducor keyword），并且该标签后面跟随一个冒号。下面是一个针对 while 循环体的标签语法，同样的规则适用于所有的循环体和条件语句。

 label name: while condition {
     statements
 }

*/

/*

这个版本的游戏使用 while 循环和 switch 语句来实现游戏的逻辑。while 循环有一个标签名 gameLoop，来表明它是游戏的主循环。

该 while 循环体的条件判断语句是 while square !=finalSquare，这表明你必须刚好落在方格25中。

*/

let finalSquare = 25
var board = [Int](repeating: 0, count: finalSquare + 1)
board[03] = +08; board[06] = +11; board[09] = +09; board[10] = +02
board[14] = -10; board[19] = -11; board[22] = -02; board[24] = -08
var square = 0
var diceRoll = 0

gameLoop: while square != finalSquare {
    diceRoll += 1
    if diceRoll == 7 { diceRoll = 1 }
    switch square + diceRoll {
    case finalSquare:
        print("骰子数刚好使玩家移动到最终的方格里，游戏结束")
        break gameLoop
    case let newSquare where newSquare > finalSquare:
        print("骰子数将会使玩家的移动超出最后的方格，那么这种移动是不合法的，玩家需要重新掷骰子")
        continue gameLoop
    default:
        print("合法移动，做正常的处理 \(diceRoll) \(square)")
        square += diceRoll
        square += board[square]
    }
}
print("Game over!")

/*
注意

如果上述的 break 语句没有使用 gameLoop 标签，那么它将会中断 switch 语句而不是 while 循环。使用 gameLoop 标签清晰的表明了 break 想要中断的是哪个代码块。

同时请注意，当调用 continue gameLoop 去跳转到下一次循环迭代时，这里使用 gameLoop 标签并不是严格必须的。因为在这个游戏中，只有一个循环体，所以 continue 语句会影响到哪个循环体是没有歧义的。然而，continue 语句使用 gameLoop 标签也是没有危害的。这样做符合标签的使用规则，同时参照旁边的 break gameLoop，能够使游戏的逻辑更加清晰和易于理解。
*/

