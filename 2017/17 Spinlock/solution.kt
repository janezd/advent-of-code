fun main(args: Array<String>) {
    var buffer = mutableListOf(0)
    var pos = 0
    (1..2017).forEach {
        pos = (pos + 354) % buffer.size
        buffer.add(pos + 1, it)
        pos = (pos + 1) % buffer.size
    }
    println(buffer[(pos + 1) % buffer.size])

    pos = 0
    var after0 = 0
    (1..50000000).forEach {
        pos = (pos + 354) % it
        if (pos == 0) { after0 = it }
        pos = (pos + 1) % (it + 1)
    }
    println(after0)
}

//incorrect 1889
//incorrect 26954340