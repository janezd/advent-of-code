from hashlib import md5

start = b"pslxynzg"
to_check = [(start, 0, 0)]
longest = ""
while to_check:
    path, x, y = to_check.pop()
    m = md5(path).digest()
    if y > 0 and m[0] >= 176:
        to_check.append((path + b'U', x, y - 1))
    if y < 3 and m[0] & 15 >= 11:
        if x == 3 and y == 2:
            if len(path) > len(longest): # must already exceed by 1 -- all are even
                longest = path + b'D'
                print(len(longest) - len(start), longest[len(start):])
        else:
            to_check.append((path + b'D', x,  y + 1))
    if x > 0 and m[1] >= 176:
        to_check.append((path + b'L', x - 1, y))
    if x < 3 and m[1] & 15 >= 11:
        if y == 3 and x == 2:
            if len(path) > len(longest):
                longest = path + b'R'
                print(len(longest) - len(start), longest[len(start):])
        else:
            to_check.append((path + b'R', x + 1,  y))




