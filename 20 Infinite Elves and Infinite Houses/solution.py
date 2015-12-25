from itertools import count

ng = 29000000 / 11
for x in count(637560):
    sd = 0
    for i in range(1, 51):
        if x % i == 0:
            sd += x // i
    if i ** 2 == x:
        sd -= i
    if sd >= ng:
        print(sd, x)
        break
