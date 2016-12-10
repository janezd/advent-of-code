print(sum(
    sum(sides) > 2 * max(sides)
    for sides in (
        list(map(int, line.split())) for line in open("input.txt")
    )
))

