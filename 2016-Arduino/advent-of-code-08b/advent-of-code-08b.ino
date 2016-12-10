#include <string.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


bool matrix[6][50];
int pos = 0;
enum {Rect, Row, Column};
enum {Instr, WaitNum1, Num1, WaitNum2, Num2};
int state, instruction = Instr;
int num1, num2;
bool buf[50];
int line = 0;

void rect() {
    for(int x = 0; x < num1; x++) {
        for(int y = 0; y < num2; y++) {
            matrix[y][x] = true;
        }
    }
}

void row() {
    bool *r = matrix[num1];
    memcpy(buf, r + 50 - num2, num2);
    memmove(r + num2, r, 50 - num2);
    memcpy(r, buf, num2);
}

void column() {
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


byte new_char[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void to_char(int start_col) {
    for(int i = 0; i < 6; i++) {
        new_char[i] = 0;
        for(int j = 0; j < 5; j++) {
            new_char[i] = (new_char[i] << 1) + (matrix[i][start_col + j] ? 1 : 0);
        }
    }
}

void execute() {
    switch(instruction) {
        case Rect: rect(); break;
        case Row: row(); break;
        case Column: column(); break;
    }
    //printout();
}

void done() {
    tone(7, 430, 100);
    int i, j;
    int count = 0;
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 50   ; j++) {
            if (matrix[i][j]) {
                count++;
            }
        }
    }

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 50; j++) {
            Serial.print(matrix[i][j] ? 'X' : ' ');
        }
        Serial.println();
    }

    for(i = 0; i < 10; i++) {
        to_char(5 * i);
        lcd.createChar(i, new_char);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(count);
    lcd.setCursor(0, 1);
    for(i = 0; i < 10; i++) {
        lcd.write(byte(i));
    }
}

void setup() {
    lcd.begin(16, 2);
    lcd.clear();
    lcd.print("Line: ");

    Serial.begin(9600);
    memset(matrix, 0, 300);
    pinMode(7, OUTPUT);
}

bool isDigit(char c) {
    return (c >= '0') && (c <= '9');
}

void loop() {
    if (!Serial.available()) {
        return;
    }
    
    char c = Serial.read();
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
                line++;
                lcd.setCursor(6,0);
                lcd.print(line);
                digitalWrite(7, line % 2);
            }
            break;
    }
}

