import java.io.File

val rot = hashMapOf(4 to arrayOf(1, 3, 0, 2), 9 to arrayOf(2, 5, 8, 1, 4, 7, 0, 3, 6))
val ref = hashMapOf(4 to arrayOf(2, 3, 0, 1), 9 to arrayOf(6, 7, 8, 3, 4, 5, 0, 1, 2))

fun permute(s: String, permutation: Array<Int>) : String {
    return permutation.map { s[it] }.joinToString("")
}

fun main(args: Array<String>) {
    val rots = HashMap<String, String>(1000)
    File("input.txt")
      .readLines()
      .forEach {
          val (spattern, sresult) =  it.split(" => ")
          var pattern = spattern.replace("/", "")
          var result = sresult.replace("/", "")
          (1..2).forEach {
              (1..4).forEach {
                  rots[pattern] = result
                  pattern = permute(pattern, rot[pattern.length]!!)
              }
              pattern = permute(pattern, ref[pattern.length]!!)
          }
      }

    var art = listOf(".#.", "..#", "###")
    (1..18).forEach {
        var newArt = listOf<String>()
        val sq = if (art.size % 2 == 0) 2 else 3
        for(row in 0 until art.size step sq) {
            var lines = MutableList(sq + 1, {""})
            for(col in 0 until art.size step sq) {
                val patt = (row until row + sq).map { art[it].slice(col until col + sq)}.joinToString("")
                val replaced = rots[patt]!!.chunked(sq + 1)
                (0..sq).forEach { lines[it] += replaced[it] }
            }
            newArt = newArt + lines
        }
        art = newArt
    }

    println(art.joinToString("").count { it == '#' })
}