#include <stdio.h>
#include <stdlib.h>

int nums[10][4];
int *numptr = (int *)nums;
bool innum = false;
int discs;

void findrot() {
    for(int i = 0;; i++) {
        int disc;
        for(disc = 0; (disc < discs) && !((nums[disc][3] + i) % nums[disc][1]); disc++);
        if (disc == discs) {
            printf("%i\n", i);
            return;
        }
    }
}

void done() {
    discs = (numptr - (int *)nums) / 4;
    for(int j = 0; j < discs; j++) {
        nums[j][3] += j + 1;
    }
    findrot();

    nums[discs][3] = discs + 1;
    nums[discs][1] = 11;
    discs++;
    findrot();
    exit(0);
}

void loop() {
    char c = getchar();
    if (c == 'X') {
        done();
    }
    if ((c >= '0') && (c <= '9')) {
        if(innum) {
            *numptr = *numptr * 10 + c - '0';
        }
        else {
            *numptr = c - '0';
            innum = true;
        }
    }
    else if (innum) {
        numptr++;
        innum = false;
    }
}

int main() {
    for(;;) loop();
}
    