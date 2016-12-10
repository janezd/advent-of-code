dirs_x = {0, 1, 0, -1}
dirs_y = {1, 0, -1, 0}
dir = 0
x, y = 0, 0

f = io.open("input1.txt")
s = f:read()
for rot, num in string.gmatch(s, "([RL])(%d+)") do
    if rot == "R" then
        dir = dir + 1
    else
        dir = dir - 1
    end
    dir = dir % 4
    dist = tonumber(num)
    x = x + dirs_x[dir + 1] * dist
    y = y + dirs_y[dir + 1] * dist
end
print(x, y, x + y)