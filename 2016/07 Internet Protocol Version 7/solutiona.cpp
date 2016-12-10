#include <stdio.h>

char a, b, c;
int sum = 0;
char in_brackets;
bool abba[2];

void reset() {
    in_brackets = 0;
    a = b = c = -1;
    abba[0] = abba[1] = false;
}

int main() {
    int line = 1;
    reset();
    for(;;) {
        char d = getchar();
        if (d == '.') {
            printf("%i\n", sum);
            return 1;
        }
        if ((d == '[') || (d == ']')) {
            in_brackets = 1 - in_brackets;
            a = b = c = -1;
        }
        else if (d == '\n') {
            if (abba[0] && !abba[1]) {
                sum++;
            }
            reset();
            line++;
        }
        else {
            d -= 'a';
            if ((a == d) && (b == c) && (a != b)) {
                abba[in_brackets] = true;
            }
            a = b;
            b = c;
            c = d;
        }
    }
} 