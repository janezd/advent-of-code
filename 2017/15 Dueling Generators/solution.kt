fun ones(hash: Int): Int { 
    return (0..15).sumBy { (hash shr it) % 2 }
}


fun main(args: Array<String>) {
//    var a = 65L
  //  var b = 8921L
    var a = 679L
    var b = 771L
    println(
        (1..40000000)
        .filter {
            a = (a * 16807) % 2147483647
            b = (b * 48271) % 2147483647
            (a and 0xffff) == (b and 0xffff)
        }
        .count()
    )

    a = 679L
    b = 771L
//    a = 65L
  //  b = 8921L
    println(
        (1..5000000)
        .filter {
            do { a = (a * 16807) % 2147483647 } while (a % 4 != 0L)
            do { b = (b * 48271) % 2147483647 } while (b % 8 != 0L)
            (a and 0xffff) == (b and 0xffff)
        }
        .count()
    )

}