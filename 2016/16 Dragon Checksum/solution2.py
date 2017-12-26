input = "11101000110010100"
N = 272
#N = 35651584

n = N
while n % 2 == 0:
    n //= 2
print(n)

#input = "10000"
#N = 20
while len(input) < N:
    input = (input + "0" + input[::-1].replace("0", ".").replace("1", "0").replace(".", "1"))[:N]

#print(input)
while True:
    input = "".join(str(int(x==y)) for x, y in zip(input[::2], input[1::2]))
    if len(input) % 2:
        break
print(input, len(input))
