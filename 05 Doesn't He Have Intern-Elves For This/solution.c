#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char c, vowels = 0, two_in_row = 0, pc = -1, forbidden = 0;
    char lt[3] = "  ";
    int good = 0;
    while((c=getchar()) != EOF) {
        if (c == '\n') {
            if ((vowels >= 3) && two_in_row && !forbidden)
                good++;
            vowels = 0; two_in_row = 0; forbidden = 0; lt[0] = ' ';
            continue;
        }
        if (strchr("aeiou", c))
            vowels++;
        if (c == lt[0])
            two_in_row = 1;
        lt[1] = c;
        if (!strcmp(lt, "ab") || !strcmp(lt, "cd") || !strcmp(lt, "pq") || !strcmp(lt, "xy"))
           forbidden = 1;
        lt[0] = c;
    }
    printf("%\n", good);
}
