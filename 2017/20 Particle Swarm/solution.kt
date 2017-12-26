import kotlin.math.abs
import java.io.File
import kotlin.text.Regex

var particles = listOf<MutableList<Int>>()

fun removeDuplicates() {
    particles = particles
        .sortedBy { it[0] }
        .sortedBy { it[1] }
        .sortedBy { it[2] }
    particles = particles
        .filterIndexed(
            fun (i: Int, e: MutableList<Int>) : Boolean {
                return (i == 0 || !e.take(3).equals(particles[i - 1].take(3)))
                    && (i == particles.size - 1 || !e.take(3).equals(particles[i + 1].take(3)))
            }
        )
}

fun done() : Boolean {
   return (0..2).all { dim ->
       particles = particles.sortedBy { it[dim] }
       (1 until particles.size).all { particles[it - 1][dim + 3] <= particles[it][dim + 3] 
                                   && particles[it - 1][dim + 6] <= particles[it][dim + 6] }
   }
}

fun step() {
    particles.forEach { p -> for(i in 5 downTo 0) { p[i] += p[i + 3] } }
}

fun main(args: Array<String>) {
    val re = Regex("p=<([^,]*),([^,]*),([^,]*)>, v=<([^,]*),([^,]*),([^,]*)>, a=<([^,]*),([^,]*),([^,]*)>")
    particles = File("input.txt").readLines().map {
        re.find(it)!!.groupValues.drop(1).map { it.toInt() }.toMutableList()
    }
    println((0 until particles.size).minBy { particles[it].takeLast(3).sumBy { abs(it) } })

    removeDuplicates()
    while(!done()) {
        step()
        removeDuplicates()
    }
    println(particles.size)
}
