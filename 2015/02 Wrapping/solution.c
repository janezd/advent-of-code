#include <stdio.h>

int main(int argc, const char *argv[]) {
    int a, b, c, t, paper=0, ribbon=0;
    while(scanf("%ix%ix%i", &a, &b, &c) != EOF) {
        #define SWAP(u,v) if (u < v) { t = u; u = v; v = t; }
        SWAP(a, b); SWAP(b, c); SWAP(a, b);  /* Bubblesort, yay! */
        paper += 3 * a * b + 2 * c * (a + b);
        ribbon += 2 * (a + b) + a * b * c;
    }
    printf("Paper: %i\nRibbon: %i\n", paper, ribbon);
}
