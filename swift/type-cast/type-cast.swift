
/*
检查类型
用类型检查操作符（is）来检查一个实例是否属于特定子类型。若实例属于那个子类型，类型检查操作符返回 true，否则返回 false。

class Movie {}
class Song {}

for item in library {
    if item is Movie {
        movieCount += 1
    } else if item is Song {
        songCount += 1
    }
}
*/

/*
向下转型
某类型的一个常量或变量可能在幕后实际上属于一个子类。当确定是这种情况时，你可以尝试向下转到它的子类型，用类型转换操作符（as? 或 as!）。

因为向下转型可能会失败，类型转型操作符带有两种不同形式。条件形式 as? 返回一个你试图向下转成的类型的可选值。强制形式 as! 把试图向下转型和强制解包转换结果结合为一个操作。

当你不确定向下转型可以成功时，用类型转换的条件形式（as?）。条件形式的类型转换总是返回一个可选值，并且若下转是不可能的，可选值将是 nil。这使你能够检查向下转型是否成功。

只有你可以确定向下转型一定会成功时，才使用强制形式（as!）。当你试图向下转型为一个不正确的类型时，强制形式的类型转换会触发一个运行时错误。

for item in library {
    if let movie = item as? Movie {
        print("Movie: '\(movie.name)', dir. \(movie.director)")
    } else if let song = item as? Song {
        print("Song: '\(song.name)', by \(song.artist)")
    }
}

// Movie: 'Casablanca', dir. Michael Curtiz
// Song: 'Blue Suede Shoes', by Elvis Presley
// Movie: 'Citizen Kane', dir. Orson Welles
// Song: 'The One And Only', by Chesney Hawkes
// Song: 'Never Gonna Give You Up', by Rick Astley

转换没有真的改变实例或它的值。根本的实例保持不变；只是简单地把它作为它被转换成的类型来使用。

*/







