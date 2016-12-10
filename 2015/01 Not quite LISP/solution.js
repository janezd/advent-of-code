var s = readline();
print(eval(s.replace(/\(/g, "+1").replace(/\)/g, "-1")));

var f = 0, x;
for (x = 0; x < s.length; x++) {
    f += s[x] == '(' ? 1 : -1;
    if (f < 0) {
        print(x + 1);
        break;
    }
}
