#include <stdio.h>

int main(int argc, char *argv[]) {
    char value[] = "hxcaabcc"; //"hxbxwxba";
    char *v, *e = value + 8;
    for(;;) {
        for(v = e; (v != value) && ++*(--v) == 'z'; ) *v = 'a';
        for(v = value; (v != value + 6) && ((v[0] != v[1] - 1) || (v[0] != v[2] - 2)); v++);
        if (v == value + 6) continue;
        for(v = value; (v != value + 5) && (v[0] != v[1]); v++);
        if (v == value + 5) continue;
        for(v+=2; (v != value + 7) && (v[0] != v[1]); v++);
        if (v == value + 7) continue;
        printf("%s\n", value);
        break;
    }
}
