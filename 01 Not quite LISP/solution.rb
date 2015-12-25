data = IO.read("input.txt").strip
floor = 0
first_b = -1
data.each_char.with_index do |c, i|
    floor += c == "(" ? 1 : -1
    if floor < 0 and first_b < 0
        first_b = i + 1
    end
    print i, floor, "\n"
end
print floor, "\n"
print first_b, "\n"
