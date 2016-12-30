#include "advent.h"

signed char prog[96], *eptr=prog;

enum {INSTR, WAIT_OP1, OP1, OP2};
char state = INSTR;
signed char sgn;

void setup() {
    Serial.begin(9600);
    pinMode(2, OUTPUT);
}

void run() {
    long long regs[4];
    regs[0] = regs[1] = regs[2] = regs[3] = 0;
//    regs[2] = 1;
    signed char *ip = prog;
    while (ip - prog < eptr - prog) {
        long long op1 = ip[1] < 120 ? ip[1] : regs[ip[1] - 120];
        switch (*ip) {
            case 'j': if (op1) { ip += ip[2] * 3; continue; }
            case 'c': regs[ip[2] - 120] = op1; break;
            case 'i': regs[ip[1] - 120]++; break;
            case 'd': regs[ip[1] - 120]--; break;
        }
        ip +=  3;
//        digitalWrite(2, HIGH);
//        showNumber((long long int)(ip - prog) / 3, 0);
  //      digitalWrite(2, LOW);
    }
    showNumber(regs[0], 0, 8);
}

void loop() {
    if (!Serial.available())
        return;
        
    char c = Serial.read();
    if (c == '.') {
        run();
    }
    switch (state) {
        case INSTR:
            *eptr++ = c;
            *eptr = 0;
            sgn = 1;
            state++;
            break;
        case WAIT_OP1:
            if (c == ' ') state++;
            break;
        case OP1:
        case OP2:
            if (c <= ' ') {
                *eptr++ *= sgn;
                *eptr = 0;
                sgn = 1;
                if ((c < ' ') && (state == OP1)) {
                    state++;
                    eptr++;
                }
                state = state == OP2 ? INSTR : OP2;
            }
            else if (c >= 'a') *eptr = 120 + c - 'a';
            else if (c == '-') sgn = -1;
            else *eptr = 10 * *eptr + c - '0';
            break;
    }
}

