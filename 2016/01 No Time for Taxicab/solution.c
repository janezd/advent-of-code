#include <stdio.h>
#include <stdlib.h>

char const *input = "R4, R3, R5, L3, L5, R2, L2, R5, L2, R5, R5, R5, R1, R3, L2, L2, L1, R5, L3, R1, L2, R1, L3, L5, L1, R3, L4, R2, R4, L3, L1, R4, L4, R3, L5, L3, R188, R4, L1, R48, L5, R4, R71, R3, L2, R188, L3, R2, L3, R3, L5, L1, R1, L2, L4, L2, R5, L3, R3, R3, R4, L3, L4, R5, L4, L4, R3, R4, L4, R1, L3, L1, L1, R4, R1, L4, R1, L1, L3, R2, L2, R2, L1, R5, R3, R4, L5, R2, R5, L5, R1, R2, L1, L3, R3, R1, R3, L4, R4, L4, L1, R1, L2, L2, L4, R1, L3, R4, L2, R3, L1, L5, R4, R5, R2, R5, R1, R5, R1, R3, L3, L2, L2, L5, R2, L2, R5, R5, L2, R3, L5, R5, L2, R4, R2, L1, R3, L5, R3, R2, R5, L1, R3, L2, R2, R1";

int main() {
    char state = 0;
    int steps;
    int x = 0, y = 0;
    int dir = 0;
    for(char const *chr = input;; chr++) {
        if (state == 0) {
            if ((*chr == 'L') || (*chr == 'R')) {
                dir = (4 + dir + (*chr == 'L' ? -1 : 1)) % 4;
                state = 1;
                steps = 0;
            }
        }
        else {
            if ((*chr >= '0') && (*chr <= '9')) {
                steps = 10 * steps + (*chr - '0');
            }
            else {
                switch (dir) {
                    case 0: y += steps; break;
                    case 1: x += steps; break;
                    case 2: y -= steps; break;
                    case 3: x -= steps; break;
                }
                state = 0;
                printf("%i %i %i %i\n", x, y, steps, dir);
            }
            if (!*chr) {
                break;
            }
        }
    }   
    printf("%i", abs(x) + abs(y));
}