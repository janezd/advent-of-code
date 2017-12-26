#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char line[80], *lptr;

#define N 8
char password[] = "abcdefgh", temp[10];

//#define N 5
//char password[] = "abcde", temp[10];

#define SWAP(x,y) { t = password[x]; password[x] = password[y]; password[y] = t; }
#define GETINT(x) (line[x] - '0')
#define GETCHARPOS(x) (strchr(password, line[x]) - password)

void process_line() {
    int pos1, pos2, i;
    char t;
    if (*line == 's') {  // swap
        if (line[5] == 'l') {
            pos1 = GETCHARPOS(12);
            pos2 = GETCHARPOS(26);
        }
        else {
            pos1 = GETINT(14);
            pos2 = GETINT(30);
        }
        SWAP(pos1, pos2);
    }
    else if ((*line == 'r') && (line[1] == 'o')) { // rotate
        strcpy(temp, password);
        if (line[7] == 'l')
            pos1 = N - GETINT(12);
        else if (line[7] == 'r')
            pos1 = GETINT(13);
        else {
            pos1 = GETCHARPOS(35);
            pos1 += pos1 >= 4 ? 2 : 1;
            pos1 = pos1 % N;
        }
        if (pos1) {
            memcpy(password, temp + N - pos1, pos1);
            memcpy(password + pos1, temp, N - pos1);
        }
    }
    else if (*line == 'r') {  // reverse
        pos1 = GETINT(18);
        pos2 = GETINT(28);
        for(i = (pos2 - pos1 + 1) / 2; i--; )
            SWAP(pos1 + i, pos2 - i);
    }
    else { // move
        pos1 = GETINT(14);
        pos2 = GETINT(28);
        t = password[pos1];
        if (pos1 < pos2)
            for(i = pos1; i < pos2; i++)
                password[i] = password[i + 1];
        else {
            for(i = pos1; i > pos2; i--)
                password[i] = password[i - 1];
        }
        password[pos2] = t;
    }
}

void setup() {
    lptr = line;
}

void done() {
    printf("%s\n", password);
    exit(0);
}

void loop() {
    *lptr++ = getchar();
    if (lptr[-1] == '.')
        done();
    if (lptr[-1] == '\n') {
        process_line();
        printf("%s\n", password);
        lptr = line;
    }
}

int main() {
    setup();
    for(;;)
        loop();
}