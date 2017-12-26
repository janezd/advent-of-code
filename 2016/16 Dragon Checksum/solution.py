input = seed = "11101000110010100"
N = 272
#N = 35651584

#input = "10000"
#N = 20
while len(input) < N:
    input = (input + "0" + input[::-1].replace("0", ".").replace("1", "0").replace(".", "1"))[:N]

while True:
    input = "".join(str(int(x==y)) for x, y in zip(input[::2], input[1::2]))
    print(input)
    if len(input) % 2:
        break

s = []
for i in range(N):
    rep = i // (len(seed) + 1)
    inre = i % (len(seed) + 1)
    if inre == len(seed):
        n = rep + 1
        c = str(int((((n & -n) << 1) & n) != 0))
    elif rep % 2 == 0:
        c = seed[inre]
    else:
        c = str(1 - int(seed[-inre-1]))
    s.append(c)
    print(c, end="")
print()

lb = N & -N
res = ""
t = iter(s)
for i in range(N // lb):
    st = []
    for j in range(1, 1 + lb):
        st.append(next(t))
        print("v", end="")
        while not j & 1:
            print("z", end="")
            st.append(int(st.pop() == st.pop()))
            j >>= 1
    res += str(st[0])
print()
print(res)
#print("".join(str(int((((n & -n) << 1) & n) != 0)) for n in range(1, N + 1)))
