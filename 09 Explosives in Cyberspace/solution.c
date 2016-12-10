#include <stdio.h>

long compute_length(int n) {
    enum {Normal, Read_NChars, Read_Times};
    long length = 0;
    char state = Normal;
    int nchars, times;

    while(n) {
        char c = getchar();
        if (c <= 32) {
            return length;
        }
        n--;
        switch(state) {
            case Normal:
                if (c == '(') {
                    state = Read_NChars;
                    nchars = 0;
                }
                else if (state == '.') {
                    return length;
                }
                else {
                    length++;
                }
                break;
            case Read_NChars:
                if (c == 'x') {
                    state = Read_Times;
                    times = 0;
                }
                else {
                    nchars = nchars * 10 + c - '0';
                }
                break;
            case Read_Times:
                if (c == ')') {
                    state = Normal;
                    length += times * compute_length(nchars);
                    n -= nchars;
                }
                else {
                    times = times * 10 + c - '0';
                }
                break;
        }
    }
    return length;
}

int main() {
    printf("%li\n", compute_length(100000));
}
