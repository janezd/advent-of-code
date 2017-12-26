#include <stdio.h>

#define N 100
char row1[N + 1] = "^^.^..^.....^..^..^^...^^.^....^^^.^.^^....^.^^^...^^^^.^^^^.^..^^^^.^^.^.^.^.^.^^...^^..^^^..^.^^^^";
char row2[N + 1];
char *ths = row1, *nxt = row2, *t;
int safe = 0;

int main() {
    for(int i = 0; i < 400000; i++) {
        for(int j = 0; j < N; j++) {
            if (ths[j] == '.') {
                safe++;
            }
            const char l = j ? ths[j - 1] : '.';
            const char r = j + 1 < N ? ths[j + 1] : '.';
            nxt[j] = l == r ? '.' : '^';
        }
        t = ths;
        ths = nxt;
        nxt = t;
    }
    printf("%i\n", safe);
}
