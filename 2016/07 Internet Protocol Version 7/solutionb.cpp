#include <stdio.h>

char a, b;
int sum = 0;
int in_brackets;

char pairs[26 * 26];

void reset() {
    in_brackets = 0;
    a = b = -1;
    for(int i=0; i < 26*26; i++) {
        pairs[i] = 0;
    }
}


int main() {
    int line = 1;
    reset();
    for(;;) {
        char c = getchar();
        if (c == '.') {
            printf("%i\n", sum);
            return 1;
        }
        if (c == '[') {
            in_brackets = 1;
            a = b = -1;
        }
        else if (c == ']') {
            in_brackets = 0;
            a = b = -1;
        }
        else if (c == '\n') {
            for(int i=0; i < 26*26; i++) {
                if (pairs[i] == 3) {
                    printf("%i %c%c%c %i\n", line, 97 + i % 26, 97 + i / 26, 97 + i % 26, sum);
                    sum++;
                    break;
                }
            }
            reset();
            line++;
        }
        else {
            c -= 'a';
            if ((a == c) && (a != b)) {
                if (in_brackets) {
                    pairs[a * 26 + b] |= 2;
//                    printf("%c%c%c\n", a + 97, b + 97, c + 97);
                }
                else {
                    pairs[a + b * 26] |= 1;
  //                  printf("    %c%c%c\n", a + 97, b + 97, c + 97);
                }
            }
            a = b;
            b = c;
        }
    }
} 