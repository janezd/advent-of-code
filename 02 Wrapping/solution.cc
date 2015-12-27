#include <iostream>
#include <algorithm>

int main(int argc, const char *argv[]) {
    int a, b, c, t, paper=0, ribbon=0;
    char foo;

    for(;;) {
        std::cin >> a >> foo >> b >> foo >> c;
        if (std::cin.eof()) break;
        #define SORT(u,v) if (u > v) std::swap(u, v)
        SORT(a, b); SORT(b, c); SORT(a, b);  /* Bubblesort, yay! */
        paper += 3 * a * b + 2 * c * (a + b);
        ribbon += 2 * (a + b) + a * b * c;
    }
    printf("Paper: %i\nRibbon: %i\n", paper, ribbon);
}
