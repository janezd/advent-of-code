print(len([s for s in open("input.txt")
           if sum(x in "aeiou" for x in s) >= 3 and
           any(x == y for x, y in zip(s, s[1:])) and
           not {s[i:i+2] for i in range(len(s))} & {"ab", "cd", "pq", "xy"}]))


