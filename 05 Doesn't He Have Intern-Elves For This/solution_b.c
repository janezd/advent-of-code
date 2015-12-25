#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int two_pairs = 0, two = 0;
    char c, pc = 0, ppc = 1;
    char pairs[26*26];
    int good = 0;
    memset(pairs, 0, 26*26);
    while((c=getchar()) != EOF) {
        if (c == '\n') {
            if (two_pairs && two)
                good++;
            two_pairs = two = pc = 0; ppc = 1;
            memset(pairs, 0, 26*26);
            continue;
        }
        if (c == ppc) two = 1;
        if (pc && pairs[c + 26 * pc - 27*97]++) {
            if ((c == pc) && (pc == ppc)) pc = 0; // doesn't count: three in row; but allow four
            else two_pairs = 1;
        }
        ppc = pc; pc = c;
    }
    printf("%i\n", good);
}
