#include <stdio.h>

#define N 3014387

int main() {
    long m;
    for(m = 1; m < N; m *= 2);
    m /= 2;
    printf("%li\n", (N ^ m) << 1);

    for(m = 1; m < N; m *= 3);
    m /= 3;
    if (N <= 2 * m)
        m = N - m;
    else
        m = 2 * N - 3 * m;
    printf("%li\n", m);
}