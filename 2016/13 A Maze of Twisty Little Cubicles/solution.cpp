#include <stdlib.h>
#include <stdio.h>

#define N 1364

unsigned char map[48][12];

inline char get(char x, char y) { return (map[y][x >> 2] >> ((x & 3) << 1)) & 3; }
inline void set(char x, char y, unsigned char v) {
    unsigned char &c = map[y][x >> 2], shift = (x & 3) << 1;
    c = (c & (0xff ^ (3 << shift))) | (v << shift);
    }

void compute_map() {
    for(int y = 0; y < 48; y++) {
        for(int x = 0; x < 48; x++) {
            long n = x * (x + 3 + 2 * y) + y * (1 + y) + N;
            char odd = 1;
            while(n) {
                odd ^= (n & 1);
                n >>= 1;
            }
            set(x, y, odd ? 0 : 3);
        }
    }
}

void print_map() {
    printf("\n\n");
    for(int y = 0; y < 48; y++) {
        for(int x = 0; x < 48; x++) {
            unsigned char v = get(x, y);
            if ((y == 31) && (x == 39)) { printf("%c", '8'); continue; }
            if (v == 0) printf("%c", ' ');
            if (v == 1) printf("%c", 'O');
            if (v == 2) printf("%c", '.');
            if (v == 3) printf("%c", 'x');
        }
        printf("\n");
    }
}

#define INC(x, y) { if (!get(x, y)) set(x, y, 3 - exp_now); }

bool expand(char exp_now) {
    for(int x = 0; x < 48; x++) {
        for(int y = 0; y < 48; y++) {
            if (get(x, y) == exp_now) {
                if ((x == 31) && (y == 39)) return true;
                if (x) INC(x - 1, y);
                if (x < 35) INC(x + 1, y);
                if (y) INC(x, y - 1);
                if (y < 40) INC(x, y + 1);
                set(x, y, 3);
            }
        }
    }
    return false;
}

void setup() {
    compute_map();
    set(1, 1, 1);
}

int steps = 0;
char exp_now = 1;
void loop() {
    if (expand(exp_now)) {
        printf("%i\n", steps);
        exit(0);
    }
    steps++;
    exp_now = 3 - exp_now;
}

int main() {
    setup();
    for(;steps < 100;) {
        loop();
    }
    
}