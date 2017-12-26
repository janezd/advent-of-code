#include <stdio.h>
#include <string.h>

char seed[] = "11101000110010100";
char seedlen = strlen(seed);

char dragon(long i) {
    long rep = i / (seedlen + 1);
    long inre = i % (seedlen + 1);
    if (inre == seedlen) {
        rep++;
        return (((rep & -rep) << 1) & rep) != 0;
    }
    else if (rep & 1)
        return '1' - seed[seedlen - inre - 1];
    else
        return seed[inre] - '0';
}

void compute(long n, char *res) {
    char stack[32], *ptr;
    long chunk_size = n & -n;
    printf("cd %li\n", chunk_size);
    for(long chunks = n / chunk_size, counter = 0; chunks--;) {
        ptr = stack;
        for(long i = 1; i <= chunk_size; i++) {
            *ptr++ = dragon(counter++);
            for(long j = i; !(j & 1); j >>= 1) {
                char p1 = *--ptr;
                char p2 = *--ptr;
                *ptr++ = (p1 == p2);
            }
        }
        *res++ = '0' + *stack;
    }
    *res = 0;
    printf("\n");
}

char res1[32], res2[32];

int main() {
    compute(272, res1);
    printf("%s\n", res1);

    compute(35651584, res2);
    printf("%s\n", res2);
}
