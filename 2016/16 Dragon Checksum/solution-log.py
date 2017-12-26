from itertools import count

input = seed = "11101000110010100"
N = 272
N = 35651584

def dragon():
    for i in count():
        rep = i // (len(seed) + 1)
        inre = i % (len(seed) + 1)
        if inre == len(seed):
            n = rep + 1
            yield str(int((((n & -n) << 1) & n) != 0))
        elif rep % 2 == 0:
            yield seed[inre]
        else:
            yield str(1 - int(seed[-inre-1]))

t = dragon()
print("".join(next(t) for _ in range(N)))

lb = N & -N
res = ""
t = dragon()
print(lb)
for i in range(N // lb):
    st = []
    for j in range(1, 1 + lb):
        st.append(next(t))
        while not j & 1:
            st.append(int(st.pop() == st.pop()))
            j >>= 1
    res += str(st[0])
print(res)
#print("".join(str(int((((n & -n) << 1) & n) != 0)) for n in range(1, N + 1)))
