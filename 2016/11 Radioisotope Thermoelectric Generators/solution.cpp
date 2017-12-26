#include <stdio.h>
#include <string.h>

unsigned int initial[] = {1 + 32 + 2 + 64, 4 + 8 + 256 + 16 + 512, 128, 0, 0};
unsigned int stack[1000];

#define IS_INVALID(state) (((state) & 0x1f) && (((state) >> 5) & ~(state & 0x1f)))
#define SKIP_IF(cond) { if (cond) continue; }
#define COPY_STATE(src, dest) { (dest)[0] = (src)[0]; (dest)[1] = (src)[1]; (dest)[2] = (src)[2]; (dest)[3] = (src)[3]; (dest)[4] = (src)[4]; }

int solve(unsigned int *current, int n) {
    if (!n) {
        return 0;
    }
    unsigned int *next = current + 5, *check;
    char floor = current[4];
    unsigned int state = current[floor];
    for(char dir = 1; dir >= -1; dir -= 2) {
        char next_floor = floor + dir;
        SKIP_IF((next_floor < 0) || (next_floor > 3));
        for(char i = 0; i < 10; i++) {
            unsigned int el1 = 1 << i;
            SKIP_IF(!(state & el1));
            for(char j = -1; j < i; j++) {
                unsigned int el2 = j == -1 ? 0 : (1 << j);
                SKIP_IF(el2 && !(state & el2));
                unsigned int n_this = state - el1 - el2;
                SKIP_IF(IS_INVALID(n_this));
                unsigned int n_next = current[next_floor] + el1 + el2;
                SKIP_IF(IS_INVALID(n_next));
                if ((n_next == 1023) && (next_floor == 3))
                    return 1;
                COPY_STATE(current, next);
                next[floor] = n_this;
                next[next_floor] = n_next;
                next[4] = next_floor;
                for(check = stack; check != next; check += 5)
                    if (!memcmp(check, next, 5 * sizeof(unsigned int)))
                        break;
                if (check == next) {
                    char solution_in = solve(next, n - 1);
                    if (solution_in)
                        return solution_in + 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    COPY_STATE(initial, stack);
    for(int n = 33;; n++) {
        printf("XXXXXXXXXXXX %i\n", n);
        int s = solve(stack, n);
        if (s) {
            printf("\n\n\n%i\n", s);
            break;
        }
    }
}
