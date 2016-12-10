#include <stdio.h>

int less_1=0, less_2=0;

char getchr() {
    char c = getchar();
    if ((c == '"') || (c == '\\')) less_2++;
    else if (c == '\n') less_2 += 2;
    return c;
}

int main(int args, char *argv[]) {
    char c;
    while ((c=getchr()) != EOF) {
        if (c == '\\') {
            if (getchr() == 'x') { getchr(); getchr(); less_1 += 3; }
            else less_1++;
        }
        if (c == '\n') less_1 += 2;
    }
    printf("1st part: %i\n", less_1);
    printf("2nd part: %i\n", less_2);
}

