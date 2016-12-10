data = IO.read("input.txt").lines.map { |line| line.split("x").map { |x| x.to_i }.sort }
print data.reduce(0) { |v, e| v + 3 * e[0] * e[1] + 2 * (e[0] + e[1]) * e[2]}, "\n"
print data.reduce(0) { |v, e| v + 2 * (e[0] + e[1]) + e.reduce(:*) }, "\n"