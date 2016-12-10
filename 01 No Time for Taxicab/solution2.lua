dirs_x = {0, 1, 0, -1}
dirs_y = {1, 0, -1, 0}
dir = 0
x, y = 0, 0

visited = {}

f = io.open("input1.txt")
s = f:read()
done = false
for rot, num in string.gmatch(s, "([RL])(%d+)") do
    if rot == "R" then
        dir = dir + 1
    else
        dir = dir - 1
    end
    dir = dir % 4
    dist = tonumber(num)
    for i = 1, dist do
        x = x + dirs_x[dir + 1]
        y = y + dirs_y[dir + 1]
        if visited[x + 10000 * y] == nil then
            visited[x + 10000 * y] = true
        else
            if not done then
                print(x, y, math.abs(x) + math.abs(y))
                done = true
            end
        end
    end
end