fun main(args: Array<String>) {
    var p = 0
    mainLoop@ for(b in 106700 until 123701 step 17) {
       for(d in 2 until b) {
           if (b % d == 0) { p++; continue@mainLoop }
       }
    }
    println(p)
}