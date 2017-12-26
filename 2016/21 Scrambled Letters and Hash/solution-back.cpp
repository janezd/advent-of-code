#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char line[80], *lptr;

//#define N 5
//char password[] = "abcde", temp[10];

#define N 8
char password[N + 1], temp[10];

enum {SWAP, SWAP_LETTER, ROT_LEFT, ROT_RIGHT, ROT_LETTER, REVERSE, MOVE};
char prog[200], *prog_end = prog, *ip;

#define GETINT(x) (line[x] - '0')
#define GETCHAR(x) (line[x] - 'a')
#define PACK_ARGS(x,y) (((x) << 4) | (y))

#define DO_SWAP(x,y) { t = password[x]; password[x] = password[y]; password[y] = t; }
#define DO_ROT_RIGHT(x) { if (x) { memcpy(temp, password, N); memcpy(password, temp + N - (x), (x));  memcpy(password + (x), temp, N - (x)); }}

#define GETCHARPOS(x) (strchr(password, x + 'a') - password)

void compile_line() {
    int pos1, pos2, i;
    char t;
    if (*line == 's') {  // swap
        if (line[5] == 'l') {
            *prog_end++ = SWAP_LETTER;
            *prog_end++ = PACK_ARGS(GETCHAR(12), GETCHAR(26));
        }
        else {
            *prog_end++ = SWAP;
            *prog_end++ = PACK_ARGS(GETINT(14), GETINT(30));
        }
    }
    else if ((*line == 'r') && (line[1] == 'o')) { // rotate
        if (line[7] == 'l') {
            *prog_end++ = ROT_LEFT;
            *prog_end++ = PACK_ARGS(GETINT(12), 0);
        }
        else if (line[7] == 'r') {
            *prog_end++ = ROT_RIGHT;
            *prog_end++ = PACK_ARGS(GETINT(13), 0);
        }
        else {
            *prog_end++ = ROT_LETTER;
            *prog_end++ = PACK_ARGS(GETCHAR(35), 0);
        }
    }
    else if (*line == 'r') {  // reverse
        *prog_end++ = REVERSE;
        *prog_end++ = PACK_ARGS(GETINT(18), GETINT(28));
    }
    else { // move
        *prog_end++ = MOVE;
        *prog_end++ = PACK_ARGS(GETINT(14), GETINT(28));
    }
}

void execute() {
    int pos1, pos2, i;
    char t;
    for(char *ip = prog; ip != prog_end; ip += 2) {
        pos1 = ip[1] >> 4;
        pos2 = ip[1] & 0xf;
        switch(*ip) {
            case SWAP_LETTER: pos1 = GETCHARPOS(pos1); pos2 = GETCHARPOS(pos2); // fallthrough
            case SWAP: DO_SWAP(pos1, pos2); break;
            case ROT_LEFT: DO_ROT_RIGHT(N - pos1); break;
            case ROT_RIGHT: DO_ROT_RIGHT(pos1); break;
            case ROT_LETTER:
                pos1 = GETCHARPOS(pos1);
                pos1 += pos1 >= 4 ? 2 : 1;
                pos1 %= N;
                DO_ROT_RIGHT(pos1);
                break;
            case REVERSE:
                for(i = (pos2 - pos1 + 1) / 2; i--; ) {
                    DO_SWAP(pos1 + i, pos2 - i);
                }
                break;
            case MOVE:
                t = password[pos1];
                if (pos1 < pos2)
                    for(i = pos1; i < pos2; i++)
                        password[i] = password[i + 1];
                else {
                    for(i = pos1; i > pos2; i--)
                        password[i] = password[i - 1];
                }
                password[pos2] = t;
                break;
        }
    }
}

char map_back[] = {1, 1, 6, 2, 7, 3, 0, 4};

void rexecute() {
    int pos1, pos2, i;
    char t;
    for(char *ip = prog_end; ip != prog;) {
        ip -= 2;
        pos1 = ip[1] >> 4;
        pos2 = ip[1] & 0xf;
        switch(*ip) {
            case SWAP_LETTER: pos1 = GETCHARPOS(pos1); pos2 = GETCHARPOS(pos2); // fallthrough
            case SWAP: DO_SWAP(pos1, pos2); break;
            case ROT_LEFT: DO_ROT_RIGHT(pos1); break;
            case ROT_RIGHT: DO_ROT_RIGHT(N - pos1); break;
            case ROT_LETTER:
                pos1 = GETCHARPOS(pos1);
                pos1 = map_back[pos1];
                DO_ROT_RIGHT(N - pos1);
                break;
            case REVERSE:
                for(i = (pos2 - pos1 + 1) / 2; i--; ) {
                    DO_SWAP(pos1 + i, pos2 - i);
                }
                break;
            case MOVE:
                t = password[pos2];
                if (pos2 < pos1)
                    for(i = pos2; i < pos1; i++)
                        password[i] = password[i + 1];
                else {
                    for(i = pos2; i > pos1; i--)
                        password[i] = password[i - 1];
                }
                password[pos1] = t;
                break;
        }
    }
}

void setup() {
    lptr = line;
}

void done() {
    strcpy(password, "abcdegfh");
    execute();
    printf("%s\n", password);
    strcpy(password, "fbgdceah");
    rexecute();
    printf("%s\n", password);
    exit(0);
}

void loop() {
    *lptr++ = getchar();
    if (lptr[-1] == '.')
        done();
    if (lptr[-1] == '\n') {
        compile_line();
        lptr = line;
    }
}

int main() {
    setup();
    for(;;)
        loop();
}
