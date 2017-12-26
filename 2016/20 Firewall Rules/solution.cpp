#include <stdio.h>

#define MAX_IP 4294967295

unsigned long interval[2];

bool readline(FILE *f) {
    interval[0] = interval[1] = 0;
    unsigned long *ip = interval;
    for(;;) {
        char c = fgetc(f);
        if (c == EOF)
            return false;
        if ((c >= '0') && (c <= '9'))
            *ip = 10 * *ip + c - '0';
        else {
            ip++;
            if (ip - interval == 2) {
                return true;
            }
        }
    }
}

unsigned long find_available_from(unsigned long available) {
    for(;;) {
        char c = 0;
        FILE *f = fopen("input.txt", "r");
        for(;;) {
            if (!readline(f)) {
                fclose(f);
                return available;
            }
            if ((available >= interval[0]) && (available <= interval[1])) {
                available = interval[1] + 1;
                fclose(f);
                break;
            }
        }
    }
    return -1;
}

unsigned long find_unavailable_from(unsigned long available) {
    char c = 0;
    FILE *f = fopen("input.txt", "r");
    unsigned long unavailable = MAX_IP + 1;
    for(;;) {
        if (!readline(f)) {
            return unavailable;
        }
        if ((interval[0] > available) && (interval[0] < unavailable))
            unavailable = interval[0];
    }
    return -1;
}

unsigned long find_n_available() {
    unsigned long available = 0, unavailable;
    unsigned long n_available = 0;
    while (available <= MAX_IP) {
        available = find_available_from(available);
        unavailable = find_unavailable_from(available);
        n_available += unavailable - available;
        available = unavailable;
    }
    return n_available;
}

int main() {
    printf("First vailable: %li\n", find_available_from(0));
    printf("Number of available addresses: %li\n", find_n_available());
}