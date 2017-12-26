from hashlib import md5

dirs = (0, -1), (0, 1), (-1, 0), (1, 0)
cdirs = b"U", b"D", b"L", b"R"

start = b"pslxynzg"
to_check = [(start, 0, 0)]
i = 0
while i < len(to_check):
    path, x, y = to_check[i]
    for (dx, dy), cdir, allowed in zip(dirs, cdirs, md5(path).hexdigest()[:4]):
        if allowed > 'a':
            nx, ny = x + dx, y + dy
            npath = path + cdir
            if nx == ny == 3:
                print(npath[len(start):])
                exit()
            to_check.append((path + cdir, x + dx, y + dy))
    i += 1

