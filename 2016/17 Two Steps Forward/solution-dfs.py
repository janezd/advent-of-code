from hashlib import md5

cdirs = ".UDLR"

start = "pslxynzg"
path = "."
longest = 0
shortest = None
while True:
    path = path.rstrip("R")
    if not path:
        break
    opath, last = path[:-1], path[-1]
    h = md5((start + opath).encode("ascii")).hexdigest()
    next = cdirs.index(last) + 1
    path = opath + cdirs[next]
    if h[next - 1] > 'a':
        x, y = path.count("R") - path.count("L"), path.count("D") - path.count("U")
        if 0 <= x <= 3 and 0 <= y <= 3:
            if x == y == 3:
                if len(path) > longest:
                    print(len(path), path)
                    longest = len(path)
                if shortest is None or len(path) < shortest:
                    print(len(path), path)
                    shortest = len(path)
            else:
                path += "."
print(longest)
