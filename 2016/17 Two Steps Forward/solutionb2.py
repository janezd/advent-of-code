from hashlib import md5

start = b"pslxynzg"
to_check_next = [(start, 0, 0)]
longest = ""
while to_check_next:
    to_check = to_check_next
    to_check_next = []
    for path, x, y in to_check:
        m = md5(path).digest()
        if y > 0 and m[0] >= 176:
            to_check_next.append((path + b'U', x, y - 1))
        if y < 3 and m[0] & 15 >= 11:
            if x == 3 and y == 2:
                longest = path + b'D'
            else:
                to_check_next.append((path + b'D', x,  y + 1))
        if x > 0 and m[1] >= 176:
            to_check_next.append((path + b'L', x - 1, y))
        if x < 3 and m[1] & 15 >= 11:
            if y == 3 and x == 2:
                longest = path + b'R'
            else:
                to_check_next.append((path + b'R', x + 1,  y))

    print(len(longest) - len(start), longest[len(start):])

