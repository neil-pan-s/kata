
/*
创建和构造一个空的集合
你可以通过构造器语法创建一个特定类型的空集合：
*/

var letters = Set<Character>()
print("letters is of type Set<Character> with \(letters.count) items.")
// 打印 "letters is of type Set<Character> with 0 items."

letters.insert("a")
// letters 现在含有1个 Character 类型的值
letters = []
// letters 现在是一个空的 Set, 但是它依然是 Set<Character> 类型

var favoriteGenres: Set<String> = ["Rock", "Classical", "Hip hop"]
// favoriteGenres 被构造成含有三个初始值的集合
// var favoriteGenres: Set = ["Rock", "Classical", "Hip hop"]

favoriteGenres.contains("Funk")

for genre in favoriteGenres {
    print("\(genre)")
}
// Classical
// Jazz
// Hip hop

for genre in favoriteGenres.sorted() {
    print("\(genre)")
}
// prints "Classical"
// prints "Hip hop"
// prints "Jazz

/*
基本集合操作
下面的插图描述了两个集合-a 和 b-以及通过阴影部分的区域显示集合各种操作的结果。


使用 intersection(_:) 方法根据两个集合中都包含的值创建的一个新的集合。
使用 symmetricDifference(_:) 方法根据在一个集合中但不在两个集合中的值创建一个新的集合。
使用 union(_:) 方法根据两个集合的值创建一个新的集合。
使用 subtracting(_:) 方法根据不在该集合中的值创建一个新的集合。
*/
let oddDigits: Set = [1, 3, 5, 7, 9]
let evenDigits: Set = [0, 2, 4, 6, 8]
let singleDigitPrimeNumbers: Set = [2, 3, 5, 7]

oddDigits.union(evenDigits).sorted()
// [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
oddDigits.intersection(evenDigits).sorted()
// []
oddDigits.subtracting(singleDigitPrimeNumbers).sorted()
// [1, 9]
oddDigits.symmetricDifference(singleDigitPrimeNumbers).sorted()
// [1, 2, 9]

/*
集合成员关系和相等
下面的插图描述了三个集合-a,b 和 c,以及通过重叠区域表述集合间共享的元素。集合 a 是集合 b 的父集合，因为 a 包含了 b 中所有的元素，相反的，集合 b 是集合 a 的子集合，因为属于 b 的元素也被 a 包含。集合 b 和集合 c 彼此不关联，因为它们之间没有共同的元素。


使用“是否相等”运算符（==）来判断两个集合是否包含全部相同的值。
使用 isSubset(of:) 方法来判断一个集合中的值是否也被包含在另外一个集合中。
使用 isSuperset(of:) 方法来判断一个集合中包含另一个集合中所有的值。
使用 isStrictSubset(of:) 或者 isStrictSuperset(of:) 方法来判断一个集合是否是另外一个集合的子集合或者父集合并且两个集合并不相等。
使用 isDisjoint(with:) 方法来判断两个集合是否不含有相同的值（是否没有交集）。
*/

let houseAnimals: Set = ["🐶", "🐱"]
let farmAnimals: Set = ["🐮", "🐔", "🐑", "🐶", "🐱"]
let cityAnimals: Set = ["🐦", "🐭"]

houseAnimals.isSubset(of: farmAnimals)
// true
farmAnimals.isSuperset(of: houseAnimals)
// true
farmAnimals.isDisjoint(with: cityAnimals)
// true


