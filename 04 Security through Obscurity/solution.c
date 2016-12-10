#include <string.h>
#include <stdio.h>

char counts[26];
int sector;
char common[5], *in_commons;
int total = 0;

void reset() {
    memset(counts, 0, 26);
    sector = 0;
    in_commons = NULL;
}

bool valid_room() {
    int i, j;
    char letters[27];
    for(i = 0; i < 26; i++) {
        for(j = i; (j > 0) && (counts[i] > counts[letters[j - 1]]); j--) {
            letters[j] = letters[j - 1];
        }
        letters[j] = i;
    }
    return !memcmp(common, letters, 5);
}

bool loop() {
    char b = getchar();
    if ((b >= 'a') && (b <= 'z')) {
        if (!in_commons) {
            counts[b - 'a']++;
        }
        else {
            *in_commons++ = b - 'a'; 
        }
    }
    else if ((b >= '0') && (b <= '9')) {
        sector = sector * 10 + b - '0';
    }
    else if (b == '[') {
        in_commons = common;
    }
    else if (b == ']') {
        if (valid_room()) {
            total += sector;
        }
        reset();
    }
    else if (b == '.') {
        printf("%i\n", total);
        return false;
    }
    return true;
}

int main() {
    while(loop());
}

