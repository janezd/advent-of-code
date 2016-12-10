#include <stdio.h>

int main(int argc, const char *argv[]) {
    int floor=0, step=1, base=-1, c;
    for(; (c=getchar()) != EOF; step++) {
        switch (c) {
            case '(': floor++; break;
            case ')': floor--; break;
        }
        if ((floor < 0) && (base == -1)) {
            base = step;
        }
    }
    printf("Last floor: %i\nFirst below ground: %i\n", floor, base);
}
