#include "advent.h"

unsigned char instructions[210][2];
unsigned char bots[210][2];
unsigned char outputs[21];

char state;
char skip;
int num, num_acc;
int line = 0;
unsigned char to_output;
unsigned char bot_num, chip_num;
enum {WaitType,
      BWaitBotNum, BBotNum,
      BSkipToWhere1, BWhere1, BWaitNum1, BNum1,
      BSkipToWhere2, BWhere2, BWaitNum2, BNum2,
      VWaitNum1, VNum1, VWaitNum2, VNum2};
char wait_num_states[] = {BWaitBotNum, BWaitNum1, BWaitNum2, VWaitNum1, VWaitNum2};

int answ1, answ2;

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

void finished() {
    for(;;) {
        lcd.clearDisplay(0);
        showNumber(answ1, 0);
        tone(2, 200, 10);
        delay(1000);
        showNumber(answ2, 0, 8);
        tone(2, 200, 10);
        delay(1000);
    }        
}

void compute() {
    unsigned char bot;
    for(;;) {
        for(bot = 0; (bot < 210) && (bots[bot][1] == 255); bot++);
        if (bot == 210) {
            answ2 = outputs[0] * outputs[1] * outputs[2];
            finished();
        }
        if ((bots[bot][0] == 17) && (bots[bot][1] == 61)) {
            answ1 = bot;
        }
        lcd.clearDisplay(0);
        showNumber(bots[bot][0], 4);
        showNumber(bots[bot][1], 0);
        tick();
        give(instructions[bot][0], bots[bot][0]);
        give(instructions[bot][1], bots[bot][1]);
        bots[bot][1] = 255;
    }
}

void newline() {
    state = WaitType;
    num_acc = -1;
    skip = 0;
    showNumber(++line, 0);
}

void setup() {
    for(int i = 0; i < 210; i++) {
        bots[i][0] = bots[i][1] = 255;
    }
    newline();

    pinMode(2, OUTPUT);
    Serial.begin(19200);
}

void loop() {
    if (!Serial.available())
        return;
        
    int c = Serial.read();
    if ((c == '.') || (c < 0)) {
        compute();
    }
    if (skip) {
        if (!skip--)
            state++;
        return;
    }
    bool digit = (c >= '0') && (c <= '9');
    for(int i = 0; i < 5; i++) {
        if (wait_num_states[i] == state) {
            if (!digit)
                return;
            num_acc = 0;
            state++;
            break;
        }
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

