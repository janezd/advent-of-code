#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned char instructions[210][2];
unsigned char bots[210][2];
unsigned char outputs[21];

char state;
char skip;
int num, num_acc;
unsigned char to_output;
unsigned char bot_num, chip_num;
enum {WaitType,
      BWaitBotNum, BBotNum,
      BSkipToWhere1, BWhere1, BWaitNum1, BNum1,
      BSkipToWhere2, BWhere2, BWaitNum2, BNum2,
      VWaitNum1, VNum1, VWaitNum2, VNum2};
char wait_num_states[] = {BWaitBotNum, BWaitNum1, BWaitNum2, VWaitNum1, VWaitNum2};


void give(unsigned char where, unsigned char num) {
    if (where >= 230)
        outputs[where - 230] = num;
    else
        if (num > bots[where][0])
            bots[where][1] = num;
        else {
            bots[where][1] = bots[where][0];
            bots[where][0] = num;
        }
}

void compute() {
    unsigned char bot;
    for(;;) {
        for(bot = 0; (bot < 210) && (bots[bot][1] == 255); bot++);
        if (bot == 210)
            return;
        if ((bots[bot][0] == 17) && (bots[bot][1] == 61)) {
            printf("Bot: %i\n", bot);
        }
        give(instructions[bot][0], bots[bot][0]);
        give(instructions[bot][1], bots[bot][1]);
        bots[bot][1] = 255;
    }
}

void printout() {
    printf("Product: %li\n\n", long(outputs[0]) * outputs[1] * outputs[2]);
    for(unsigned char i = 0; i < 21; i++) {
        printf("%i ", outputs[i]);
    }
    printf("\n");
}

void newline() {
    state = WaitType;
    num_acc = -1;
    skip = 0;
}

void setup() {
    memset(bots, 255, 420);
    newline();
}

void loop() {
    int c = getchar();
    if ((c == '.') || (c < 0)) {
        compute();
        printout();
        exit(0);
    }
    if (skip) {
        if (!skip--)
            state++;
        return;
    }
    bool digit = (c >= '0') && (c <= '9');
    if (memchr(wait_num_states, state, 5)) {
        if (!digit)
            return;
        num_acc = 0;
        state++;
    }
    if (num_acc >= 0) {
        if (digit) {
            num_acc = num_acc * 10 + c - '0';
            return;
        }
        num = num_acc;
        num_acc = -1;
    }
    switch (state) {
        case WaitType: state = c == 'b' ? BWaitBotNum : VWaitNum1; return;
        case BBotNum: bot_num = num; skip = 12; break;
        case BWhere1: to_output = c == 'b' ? 0 : 230; break;
        case BNum1: instructions[bot_num][0] = num + to_output; skip = 11; break;
        case BWhere2: to_output = c == 'b' ? 0 : 230; break;
        case BNum2: instructions[bot_num][1] = num + to_output; newline(); return;

        case VNum1: chip_num = num; break;
        case VNum2: give(num, chip_num); newline(); return;
    }
    state++;
}

int main() {
    setup();
    for(;;) {
        loop();
    }
}