#include <stdio.h>
#include <string.h>

bool matrix[6][50];
int pos = 0;
enum {Rect, Row, Column};
enum {Instr, WaitNum1, Num1, WaitNum2, Num2};
int state, instruction = Instr;
int num1, num2;
bool buf[50];

void rect() {
    printf("rect %i x %i\n", num1, num2);
    for(int x = 0; x < num1; x++) {
        for(int y = 0; y < num2; y++) {
            matrix[y][x] = true;
        }
    }
}

void row() {
    printf("row %i by %i\n", num1, num2);
    bool *r = matrix[num1];
    memcpy(buf, r + 50 - num2, num2);
    memcpy(r + num2, r, 50 - num2);
    memcpy(r, buf, num2);
}

void column() {
    printf("col %i by %i\n", num1, num2);
    int i, j;
    for(i = 6 - num2, j = 0; i < 6; i++, j++) {
        buf[j] = matrix[i][num1];
    }
    for(i = 6; --i >= num2; ) {
        matrix[i][num1] = matrix[i - num2][num1];
    }
    for(i = 0; i < num2; i++) {
        matrix[i][num1] = buf[i];
    }
}

void printout() {
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 50; j++) {
            printf("%c", matrix[i][j] ? 'X' : ' ');
        }
        printf("\n");
    }
}

void execute() {
    switch(instruction) {
        case Rect: rect(); break;
        case Row: row(); break;
        case Column: column(); break;
    }
}

void done() {
    int count = 0;
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 50   ; j++) {
            if (matrix[i][j]) {
                count++;
            }
        }
    }
    printout();
    printf("%i\n", count);
}

void setup() {
    memset(matrix, 0, 300);
}

bool isDigit(char c) {
    return (c >= '0') && (c <= '9');
}

void loop() {
    char c = getchar();
    pos++;
    if (c == '.') {
        done();
    }
    switch (state) {
        case Instr:
            if ((pos == 2) && (c == 'e')) {
                instruction = Rect;
                state = WaitNum1;
            }
            if (pos == 8) {
                instruction = c == 'r' ? Row : Column;
                state = WaitNum1;
            }
            break;
        case WaitNum1:
            if (isDigit(c)) {
                state = Num1;
                num1 = c - '0';
            }
            break;
        case Num1:
            if (isDigit(c)) {
                num1 = 10 * num1 + c - '0';
            }
            else {
                state = WaitNum2;
            }
            break;
        case WaitNum2:
            if (isDigit(c)) {
                state = Num2;
                num2 = c - '0';
            }
            break;
        case Num2:
            if (isDigit(c)) {
                num2 = 10 * num2 + c - '0';
            }
            else {
                execute();
                state = Instr;
                pos = 0;
            }
            break;
    }
}

int main() {
    setup();
    for(;;) {
        loop();
    }
}