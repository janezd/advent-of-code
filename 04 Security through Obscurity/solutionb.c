#include <string.h>
#include <stdio.h>

char counts[26];
int sector;
char common[5], *in_commons;
int total = 0;
char text[80], *in_text;

void reset() {
    memset(counts, 0, 26);
    sector = 0;
    in_commons = NULL;
    in_text = text;
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
            *in_text++ = b;
        }
        else {
            *in_commons++ = b - 'a'; 
        }
    }
    else if (b == '-') {
        *in_text++ = b;
    }
    else if ((b >= '0') && (b <= '9')) {
        sector = sector * 10 + b - '0';
    }
    else if (b == '[') {
        in_commons = common;
    }
    else if (b == ']') {
        if (valid_room()) {
            *in_text = 0;
            for(char *tt = text; *tt; tt++) {
                *tt = *tt == '-' ? ' ' : (*tt - 'a' + sector) % 26 + 'a';
            }
            if (strstr(text, "north")) {
                printf("%i: %s\n", sector, text);
            }
        }
        reset();
    }
    else if (b == '.') {
        return false;
    }
    return true;
}

int main() {
    reset();
    while(loop());
}

