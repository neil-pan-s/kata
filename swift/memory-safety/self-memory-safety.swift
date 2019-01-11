
/*
方法里 self 的访问冲突
一个结构体的 mutating 方法会在调用期间对 self 进行写访问。例如，想象一下这么一个游戏，每一个玩家都有血量，受攻击时血量会下降，并且有敌人的数量，使用特殊技能时会减少敌人数量。

struct Player {
    var name: String
    var health: Int
    var energy: Int

    static let maxHealth = 10
    mutating func restoreHealth() {
        health = Player.maxHealth
    }
}
在上面的 restoreHealth() 方法里，一个对于 self 的写访问会从方法开始直到方法 return。在这种情况下，restoreHealth() 里的其它代码不可以对 Player 实例的属性发起重叠的访问。下面的 shareHealth(with:) 方法接受另一个 Player 的实例作为 in-out 参数，产生了访问重叠的可能性。

extension Player {
    mutating func shareHealth(with teammate: inout Player) {
        balance(&teammate.health, &health)
    }
}

var oscar = Player(name: "Oscar", health: 10, energy: 10)
var maria = Player(name: "Maria", health: 5, energy: 10)
oscar.shareHealth(with: &maria)  // 正常
上面的例子里，调用 shareHealth(with:) 方法去把 oscar 玩家的血量分享给 maria 玩家并不会造成冲突。在方法调用期间会对 oscar 发起写访问，因为在 mutating 方法里 self 就是 oscar，同时对于 maria 也会发起写访问，因为 maria 作为 in-out 参数传入。过程如下，它们会访问内存的不同位置。即使两个写访问重叠了，它们也不会冲突。



当然，如果你将 oscar 作为参数传入 shareHealth(with:) 里，就会产生冲突：

oscar.shareHealth(with: &oscar)
// 错误：oscar 访问冲突
mutating 方法在调用期间需要对 self 发起写访问，而同时 in-out 参数也需要写访问。在方法里，self 和 teammate 都指向了同一个存储地址 —— 就像下面展示的那样。对于同一块内存同时进行两个写访问，并且它们重叠了，就此产生了冲突。
*/

