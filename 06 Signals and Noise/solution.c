#include <stdio.h>

short frequencies[8][26];
char i, j, b;

short argmax(short *f) {
    short *m=f, *t=f;
    for(char i=26; i--; t++) {
        if (*t > *m) {
            m = t;
        }
    }
    return m - f; 
}

short argmin(short *f) {
    short *m=f, *t=f;
    for(char i=26; i--; t++) {
        if (*t < *m) {
            m = t;
        }
    }
    return m - f; 
}

int main() {
    for(i = 0; i < 8; i++) {
        for(j = 0; j < 26; j++) {
            frequencies[i][j] = 0;
        }
    }
    i = 0;
    for(;;) {
        b = getchar();
        if (b == '.') {
            break;
        }
        else if ((b >= 'a') && (b <= 'z')) {
            frequencies[i++][b - 'a']++;
        }
        else {
            i = 0;
        }
    }
    for(i=0; i<8; i++) {
        printf("%c", 97 + argmax(frequencies[i]));
    }
    printf("\n");
    for(i=0; i<8; i++) {
        printf("%c", 97 + argmin(frequencies[i]));
    }
}