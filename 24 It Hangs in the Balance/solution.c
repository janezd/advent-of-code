#include <stdio.h>

int numbers[] = {113, 109, 107, 103, 101, 97, 89, 83, 79, 73, 71, 67,
                 61, 59, 53, 47, 43, 41, 31, 29, 23, 19, 17, 13, 11, 5, 3, 1, 0};

#define G 4
#define N 28

int totals[G];
int total = 0;
char allocs[N], *eallocs = allocs + N;
int tot_min = N;
long min_qe, poss_qe;
long qes[G];
int in_sleighs[G];

void to_sum(char *n, int *nums) {
    int i, ms;
    char a, *p;
    if (!*nums) {
        for(i = 0; i < G; i++) {
            in_sleighs[i] = 0;
            qes[i] = 1;
        }
        for(i = 0; i < N; i++) {
            a = allocs[i];
            in_sleighs[a]++;
            qes[a] *= numbers[i];
        }
        ms = in_sleighs[0];
        for(i=1; i < G; i++)
            if (in_sleighs[i] < ms)
                ms = in_sleighs[i];
        if (ms <= tot_min) {
            if (ms < tot_min) {
                tot_min = ms;
                min_qe = poss_qe;
            }
            for(i = 0; i < G; i++)
                if ((in_sleighs[i] == ms) && (qes[i] < min_qe)) {
                    min_qe = qes[i];
                    printf("%i %li\n", ms, min_qe);
                }
        }
        return;
    }

    ms = 0;
    for(p = allocs; p != n; p++) {
        if (*p > ms)
            ms = *p;
    }
    ms += 2;
    if(ms > G)
        ms = G;
    for(*n = 0; *n < ms; (*n)++) {
        totals[*n] += *nums;
        if (totals[*n] <= total)
            to_sum(n + 1, nums + 1);
        totals[*n] -= *nums;
    }
}

int main(int argc, char *argv[]) {
    int *p, i;
    poss_qe = 1;
    total = 0;
    for(p = numbers; *p; p++) {
        total += *p;
        poss_qe *= *p;
    }
    for(i = 0; i < G; i++) totals[i] = 0;
    total /= G;
    to_sum(allocs, numbers);
}
