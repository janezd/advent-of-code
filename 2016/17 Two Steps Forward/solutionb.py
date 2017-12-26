from hashlib import md5

dirs = (0, -1), (0, 1), (-1, 0), (1, 0)
cdirs = b"U", b"D", b"L", b"R"

start = b"pslxynzg"
to_check_next = [(start, 0, 0)]
i = 0
longest = ""
while to_check_next:
    to_check = to_check_next
    print(len(to_check[0][0]) - len(start), len(to_check))
    to_check_next = []
    for path, x, y in to_check:
        for (dx, dy), cdir, allowed in zip(dirs, cdirs, md5(path).hexdigest()):
            if allowed > 'a':
                nx, ny = x + dx, y + dy
                if nx == ny == 3:
                    longest = (path + cdir)[len(start):]
                else:
                    to_check_next.append((path + cdir, x + dx, y + dy))

    print(longest)
    print(len(longest))

