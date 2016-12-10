#include <iostream>
#include <numeric>

#define PART_2

template<class T>
void apply(T func, int *lights, int const x0, int const y0, int const x1, int const y1) {
    for(int x = x0; x <= x1; x++) {
        for(int y = y0; y <= y1; y++) {
            func(lights[x + 1000 * y]);
        }
    }
}

#ifndef PART_2
void on(int &l) { l = 1; }
void off(int &l) { l = 0; }
void toggle(int &l) { l ^= 1; }
#else
void on(int &l) { l++; }
void off(int &l) { if (l) l--; }
void toggle(int &l) { l += 2; }
#endif

int main(int argc, char *argv[]) {
    int lights[1000 * 1000];
    std::fill(lights, lights + 1000 * 1000, 0);

    std::string act;
    int x0, y0, x1, y1;
    char foo;
    std::string bar;
    for(;;) {
        std::cin >> act;
        if (std::cin.eof()) {
            break;
        }
        if (act == "turn") {
            std::cin >> act;
        }
        std::cin >> x0 >> foo >> y0 >> bar >> x1 >> foo >> y1;
        if (act == "on") {
            apply(on, lights, x0, y0, x1, y1);
        }
        if (act == "off") {
            apply(off, lights, x0, y0, x1, y1);
        }
        if (act == "toggle") {
            apply(toggle, lights, x0, y0, x1, y1);
        }
    }

    int lights_on = std::accumulate(lights, lights + 1000 * 1000, 0);
    std::cout << lights_on << std::endl;
}
