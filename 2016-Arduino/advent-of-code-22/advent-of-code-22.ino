#include "advent.h"
#include <stdlib.h>

extern const char data [] PROGMEM;

bool readline(int &pos, char &x, char &y, int &used, int &available) {
    int num[6] = {0, 0, 0, 0, 0, 0}, *numptr = num;
    bool innum = false;
    for(;;) {
        unsigned char c = pgm_read_byte(data + pos++);
        if (c == '\n') break;
        c -= '0';
        if (c <= 9) *numptr = *numptr * 10 + c;
        else if (innum) numptr++;
        innum = c <= 9;
    }
    if (numptr == num) return false;
    x = num[0];
    y = num[1];
    used = num[3];
    available = num[4];
    return true;
}

void setup() {
    Serial.begin(9600);
    pinMode(2, OUTPUT);
    lcd.clearDisplay(0);
    delay(3000);
    
    char x, y;
    int available1, used1, pos1;
    int available2, used2, pos2;
    int pairs = 0, ppairs;
    char formatted[8];
    for(pos1 = 0; readline(pos1, x, y, used1, available1); ) {
        if (!y) Serial.println("");
        sprintf(formatted, "%4i:%2i", used1, available1);
        Serial.print(formatted);
        for(pos2 = 0; readline(pos2, x, y, used2, available2) && (pos2 != pos1); ) {
            ppairs = pairs;
            pairs += (used1 && (used1 <= available2)) + (used2 && (used2 <= available1));
            if (pairs != ppairs) {
                digitalWrite(2, HIGH);
                showNumber(pairs, 0);
                digitalWrite(2, LOW);
            }
        }
    }
}

void loop() {}

#define PROGMEM
const char data [] PROGMEM = R"x(x0-y0 92T 68T 24T 73%
x0-y1 87T 73T 14T 83%
x0-y2 89T 64T 25T 71%
x0-y3 91T 64T 27T 70%
x0-y4 86T 73T 13T 84%
x0-y5 90T 71T 19T 78%
x0-y6 88T 66T 22T 75%
x0-y7 87T 72T 15T 82%
x0-y8 90T 70T 20T 77%
x0-y9 90T 71T 19T 78%
x0-y10 88T 64T 24T 72%
x0-y11 87T 67T 20T 77%
x0-y12 92T 70T 22T 76%
x0-y13 91T 64T 27T 70%
x0-y14 91T 65T 26T 71%
x0-y15 85T 73T 12T 85%
x0-y16 85T 64T 21T 75%
x0-y17 87T 71T 16T 81%
x0-y18 89T 68T 21T 76%
x0-y19 90T 66T 24T 73%
x0-y20 89T 69T 20T 77%
x0-y21 87T 68T 19T 78%
x0-y22 89T 73T 16T 82%
x0-y23 87T 66T 21T 75%
x0-y24 90T 64T 26T 71%
x1-y0 88T 65T 23T 73%
x1-y1 94T 69T 25T 73%
x1-y2 85T 70T 15T 82%
x1-y3 507T 493T 14T 97%
x1-y4 87T 72T 15T 82%
x1-y5 85T 70T 15T 82%
x1-y6 93T 65T 28T 69%
x1-y7 93T 65T 28T 69%
x1-y8 85T 73T 12T 85%
x1-y9 89T 66T 23T 74%
x1-y10 85T 65T 20T 76%
x1-y11 87T 64T 23T 73%
x1-y12 88T 64T 24T 72%
x1-y13 86T 69T 17T 80%
x1-y14 90T 65T 25T 72%
x1-y15 88T 66T 22T 75%
x1-y16 91T 67T 24T 73%
x1-y17 89T 71T 18T 79%
x1-y18 89T 70T 19T 78%
x1-y19 86T 73T 13T 84%
x1-y20 88T 64T 24T 72%
x1-y21 88T 69T 19T 78%
x1-y22 89T 65T 24T 73%
x1-y23 94T 73T 21T 77%
x1-y24 93T 71T 22T 76%
x2-y0 92T 71T 21T 77%
x2-y1 91T 69T 22T 75%
x2-y2 90T 70T 20T 77%
x2-y3 502T 490T 12T 97%
x2-y4 89T 69T 20T 77%
x2-y5 87T 65T 22T 74%
x2-y6 85T 66T 19T 77%
x2-y7 91T 72T 19T 79%
x2-y8 87T 65T 22T 74%
x2-y9 92T 69T 23T 75%
x2-y10 90T 64T 26T 71%
x2-y11 86T 73T 13T 84%
x2-y12 94T 68T 26T 72%
x2-y13 88T 72T 16T 81%
x2-y14 90T 70T 20T 77%
x2-y15 91T 67T 24T 73%
x2-y16 88T 64T 24T 72%
x2-y17 90T 66T 24T 73%
x2-y18 85T 68T 17T 80%
x2-y19 86T 71T 15T 82%
x2-y20 85T 69T 16T 81%
x2-y21 93T 70T 23T 75%
x2-y22 85T 72T 13T 84%
x2-y23 85T 71T 14T 83%
x2-y24 91T 70T 21T 76%
x3-y0 91T 70T 21T 76%
x3-y1 90T 64T 26T 71%
x3-y2 88T 69T 19T 78%
x3-y3 504T 490T 14T 97%
x3-y4 93T 66T 27T 70%
x3-y5 94T 70T 24T 74%
x3-y6 94T 68T 26T 72%
x3-y7 92T 71T 21T 77%
x3-y8 88T 67T 21T 76%
x3-y9 94T 72T 22T 76%
x3-y10 92T 64T 28T 69%
x3-y11 90T 66T 24T 73%
x3-y12 92T 69T 23T 75%
x3-y13 91T 66T 25T 72%
x3-y14 89T 64T 25T 71%
x3-y15 93T 64T 29T 68%
x3-y16 89T 71T 18T 79%
x3-y17 87T 71T 16T 81%
x3-y18 85T 67T 18T 78%
x3-y19 92T 64T 28T 69%
x3-y20 87T 64T 23T 73%
x3-y21 89T 70T 19T 78%
x3-y22 87T 67T 20T 77%
x3-y23 88T 71T 17T 80%
x3-y24 92T 69T 23T 75%
x4-y0 88T 71T 17T 80%
x4-y1 88T 67T 21T 76%
x4-y2 90T 71T 19T 78%
x4-y3 503T 494T 9T 98%
x4-y4 88T 72T 16T 81%
x4-y5 93T 72T 21T 77%
x4-y6 91T 71T 20T 78%
x4-y7 90T 71T 19T 78%
x4-y8 92T 72T 20T 78%
x4-y9 93T 73T 20T 78%
x4-y10 86T 68T 18T 79%
x4-y11 90T 73T 17T 81%
x4-y12 94T 67T 27T 71%
x4-y13 87T 69T 18T 79%
x4-y14 92T 67T 25T 72%
x4-y15 86T 64T 22T 74%
x4-y16 85T 71T 14T 83%
x4-y17 86T 73T 13T 84%
x4-y18 88T 71T 17T 80%
x4-y19 94T 64T 30T 68%
x4-y20 93T 66T 27T 70%
x4-y21 93T 70T 23T 75%
x4-y22 86T 67T 19T 77%
x4-y23 89T 73T 16T 82%
x4-y24 86T 65T 21T 75%
x5-y0 86T 66T 20T 76%
x5-y1 94T 71T 23T 75%
x5-y2 88T 65T 23T 73%
x5-y3 507T 492T 15T 97%
x5-y4 92T 70T 22T 76%
x5-y5 91T 66T 25T 72%
x5-y6 92T 66T 26T 71%
x5-y7 93T 71T 22T 76%
x5-y8 87T 64T 23T 73%
x5-y9 87T 68T 19T 78%
x5-y10 93T 65T 28T 69%
x5-y11 87T 65T 22T 74%
x5-y12 90T 73T 17T 81%
x5-y13 94T 64T 30T 68%
x5-y14 89T 66T 23T 74%
x5-y15 92T 67T 25T 72%
x5-y16 92T 73T 19T 79%
x5-y17 87T 68T 19T 78%
x5-y18 86T 65T 21T 75%
x5-y19 93T 73T 20T 78%
x5-y20 93T 68T 25T 73%
x5-y21 87T 71T 16T 81%
x5-y22 93T 71T 22T 76%
x5-y23 86T 68T 18T 79%
x5-y24 88T 67T 21T 76%
x6-y0 85T 72T 13T 84%
x6-y1 88T 72T 16T 81%
x6-y2 88T 65T 23T 73%
x6-y3 503T 497T 6T 98%
x6-y4 91T 71T 20T 78%
x6-y5 86T 68T 18T 79%
x6-y6 94T 72T 22T 76%
x6-y7 87T 67T 20T 77%
x6-y8 92T 72T 20T 78%
x6-y9 94T 64T 30T 68%
x6-y10 85T 66T 19T 77%
x6-y11 90T 65T 25T 72%
x6-y12 88T 71T 17T 80%
x6-y13 87T 66T 21T 75%
x6-y14 92T 69T 23T 75%
x6-y15 85T 71T 14T 83%
x6-y16 90T 67T 23T 74%
x6-y17 88T 68T 20T 77%
x6-y18 89T 72T 17T 80%
x6-y19 87T 71T 16T 81%
x6-y20 92T 66T 26T 71%
x6-y21 90T 67T 23T 74%
x6-y22 90T 72T 18T 80%
x6-y23 85T 67T 18T 78%
x6-y24 93T 65T 28T 69%
x7-y0 91T 67T 24T 73%
x7-y1 86T 64T 22T 74%
x7-y2 94T 65T 29T 69%
x7-y3 510T 496T 14T 97%
x7-y4 91T 65T 26T 71%
x7-y5 94T 68T 26T 72%
x7-y6 87T 69T 18T 79%
x7-y7 90T 73T 17T 81%
x7-y8 92T 73T 19T 79%
x7-y9 90T 69T 21T 76%
x7-y10 90T 64T 26T 71%
x7-y11 86T 66T 20T 76%
x7-y12 94T 67T 27T 71%
x7-y13 92T 73T 19T 79%
x7-y14 90T 73T 17T 81%
x7-y15 92T 65T 27T 70%
x7-y16 91T 67T 24T 73%
x7-y17 86T 66T 20T 76%
x7-y18 87T 69T 18T 79%
x7-y19 92T 70T 22T 76%
x7-y20 94T 68T 26T 72%
x7-y21 87T 68T 19T 78%
x7-y22 87T 72T 15T 82%
x7-y23 88T 66T 22T 75%
x7-y24 92T 66T 26T 71%
x8-y0 90T 66T 24T 73%
x8-y1 89T 67T 22T 75%
x8-y2 91T 72T 19T 79%
x8-y3 501T 497T 4T 99%
x8-y4 85T 72T 13T 84%
x8-y5 91T 67T 24T 73%
x8-y6 85T 64T 21T 75%
x8-y7 85T 64T 21T 75%
x8-y8 90T 71T 19T 78%
x8-y9 86T 71T 15T 82%
x8-y10 94T 69T 25T 73%
x8-y11 91T 71T 20T 78%
x8-y12 94T 65T 29T 69%
x8-y13 88T 70T 18T 79%
x8-y14 88T 64T 24T 72%
x8-y15 86T 71T 15T 82%
x8-y16 87T 73T 14T 83%
x8-y17 93T 71T 22T 76%
x8-y18 92T 68T 24T 73%
x8-y19 88T 69T 19T 78%
x8-y20 91T 69T 22T 75%
x8-y21 88T 69T 19T 78%
x8-y22 94T 72T 22T 76%
x8-y23 89T 71T 18T 79%
x8-y24 85T 72T 13T 84%
x9-y0 94T 68T 26T 72%
x9-y1 91T 71T 20T 78%
x9-y2 88T 72T 16T 81%
x9-y3 504T 495T 9T 98%
x9-y4 89T 67T 22T 75%
x9-y5 91T 72T 19T 79%
x9-y6 86T 71T 15T 82%
x9-y7 87T 64T 23T 73%
x9-y8 90T 71T 19T 78%
x9-y9 89T 64T 25T 71%
x9-y10 90T 70T 20T 77%
x9-y11 85T 71T 14T 83%
x9-y12 85T 66T 19T 77%
x9-y13 94T 69T 25T 73%
x9-y14 87T 70T 17T 80%
x9-y15 88T 69T 19T 78%
x9-y16 94T 67T 27T 71%
x9-y17 90T 71T 19T 78%
x9-y18 85T 67T 18T 78%
x9-y19 89T 73T 16T 82%
x9-y20 89T 72T 17T 80%
x9-y21 92T 69T 23T 75%
x9-y22 94T 67T 27T 71%
x9-y23 87T 70T 17T 80%
x9-y24 91T 68T 23T 74%
x10-y0 87T 68T 19T 78%
x10-y1 89T 71T 18T 79%
x10-y2 91T 69T 22T 75%
x10-y3 502T 494T 8T 98%
x10-y4 86T 67T 19T 77%
x10-y5 86T 68T 18T 79%
x10-y6 87T 69T 18T 79%
x10-y7 86T 64T 22T 74%
x10-y8 89T 68T 21T 76%
x10-y9 91T 72T 19T 79%
x10-y10 89T 66T 23T 74%
x10-y11 88T 65T 23T 73%
x10-y12 91T 64T 27T 70%
x10-y13 94T 65T 29T 69%
x10-y14 91T 70T 21T 76%
x10-y15 90T 73T 17T 81%
x10-y16 94T 67T 27T 71%
x10-y17 86T 70T 16T 81%
x10-y18 92T 66T 26T 71%
x10-y19 93T 73T 20T 78%
x10-y20 93T 69T 24T 74%
x10-y21 89T 69T 20T 77%
x10-y22 87T 68T 19T 78%
x10-y23 93T 64T 29T 68%
x10-y24 92T 68T 24T 73%
x11-y0 92T 73T 19T 79%
x11-y1 85T 69T 16T 81%
x11-y2 93T 70T 23T 75%
x11-y3 510T 495T 15T 97%
x11-y4 88T 73T 15T 82%
x11-y5 90T 70T 20T 77%
x11-y6 93T 72T 21T 77%
x11-y7 94T 64T 30T 68%
x11-y8 88T 64T 24T 72%
x11-y9 86T 66T 20T 76%
x11-y10 86T 66T 20T 76%
x11-y11 88T 67T 21T 76%
x11-y12 93T 67T 26T 72%
x11-y13 88T 71T 17T 80%
x11-y14 88T 66T 22T 75%
x11-y15 91T 69T 22T 75%
x11-y16 86T 72T 14T 83%
x11-y17 92T 68T 24T 73%
x11-y18 90T 73T 17T 81%
x11-y19 92T 73T 19T 79%
x11-y20 87T 66T 21T 75%
x11-y21 88T 72T 16T 81%
x11-y22 88T 66T 22T 75%
x11-y23 89T 64T 25T 71%
x11-y24 86T 73T 13T 84%
x12-y0 87T 73T 14T 83%
x12-y1 86T 65T 21T 75%
x12-y2 89T 69T 20T 77%
x12-y3 509T 492T 17T 96%
x12-y4 87T 69T 18T 79%
x12-y5 88T 70T 18T 79%
x12-y6 94T 70T 24T 74%
x12-y7 87T 70T 17T 80%
x12-y8 90T 70T 20T 77%
x12-y9 90T 72T 18T 80%
x12-y10 87T 69T 18T 79%
x12-y11 85T 73T 12T 85%
x12-y12 94T 66T 28T 70%
x12-y13 86T 66T 20T 76%
x12-y14 89T 72T 17T 80%
x12-y15 93T 73T 20T 78%
x12-y16 93T 67T 26T 72%
x12-y17 94T 71T 23T 75%
x12-y18 85T 68T 17T 80%
x12-y19 92T 70T 22T 76%
x12-y20 89T 70T 19T 78%
x12-y21 85T 72T 13T 84%
x12-y22 88T 72T 16T 81%
x12-y23 92T 67T 25T 72%
x12-y24 88T 65T 23T 73%
x13-y0 90T 69T 21T 76%
x13-y1 87T 65T 22T 74%
x13-y2 88T 70T 18T 79%
x13-y3 507T 499T 8T 98%
x13-y4 92T 66T 26T 71%
x13-y5 89T 70T 19T 78%
x13-y6 92T 65T 27T 70%
x13-y7 88T 69T 19T 78%
x13-y8 91T 68T 23T 74%
x13-y9 87T 73T 14T 83%
x13-y10 92T 67T 25T 72%
x13-y11 87T 68T 19T 78%
x13-y12 90T 72T 18T 80%
x13-y13 91T 72T 19T 79%
x13-y14 94T 71T 23T 75%
x13-y15 86T 73T 13T 84%
x13-y16 94T 71T 23T 75%
x13-y17 91T 64T 27T 70%
x13-y18 87T 64T 23T 73%
x13-y19 93T 67T 26T 72%
x13-y20 85T 64T 21T 75%
x13-y21 92T 73T 19T 79%
x13-y22 86T 72T 14T 83%
x13-y23 92T 69T 23T 75%
x13-y24 93T 70T 23T 75%
x14-y0 92T 72T 20T 78%
x14-y1 88T 71T 17T 80%
x14-y2 86T 65T 21T 75%
x14-y3 506T 495T 11T 97%
x14-y4 93T 73T 20T 78%
x14-y5 88T 68T 20T 77%
x14-y6 89T 67T 22T 75%
x14-y7 85T 70T 15T 82%
x14-y8 85T 73T 12T 85%
x14-y9 92T 71T 21T 77%
x14-y10 91T 69T 22T 75%
x14-y11 92T 71T 21T 77%
x14-y12 93T 68T 25T 73%
x14-y13 86T 68T 18T 79%
x14-y14 94T 67T 27T 71%
x14-y15 92T 67T 25T 72%
x14-y16 85T 67T 18T 78%
x14-y17 93T 73T 20T 78%
x14-y18 94T 66T 28T 70%
x14-y19 89T 67T 22T 75%
x14-y20 88T 73T 15T 82%
x14-y21 94T 73T 21T 77%
x14-y22 94T 69T 25T 73%
x14-y23 88T 69T 19T 78%
x14-y24 93T 71T 22T 76%
x15-y0 88T 71T 17T 80%
x15-y1 86T 65T 21T 75%
x15-y2 90T 68T 22T 75%
x15-y3 508T 497T 11T 97%
x15-y4 86T 71T 15T 82%
x15-y5 94T 72T 22T 76%
x15-y6 94T 65T 29T 69%
x15-y7 89T 73T 16T 82%
x15-y8 90T 72T 18T 80%
x15-y9 85T 65T 20T 76%
x15-y10 89T 65T 24T 73%
x15-y11 94T 68T 26T 72%
x15-y12 87T 67T 20T 77%
x15-y13 88T 66T 22T 75%
x15-y14 94T 71T 23T 75%
x15-y15 87T 67T 20T 77%
x15-y16 88T 68T 20T 77%
x15-y17 85T 68T 17T 80%
x15-y18 94T 72T 22T 76%
x15-y19 93T 67T 26T 72%
x15-y20 93T 71T 22T 76%
x15-y21 86T 64T 22T 74%
x15-y22 85T 72T 13T 84%
x15-y23 88T 65T 23T 73%
x15-y24 88T 73T 15T 82%
x16-y0 89T 70T 19T 78%
x16-y1 87T 66T 21T 75%
x16-y2 90T 70T 20T 77%
x16-y3 504T 492T 12T 97%
x16-y4 88T 69T 19T 78%
x16-y5 88T 64T 24T 72%
x16-y6 87T 69T 18T 79%
x16-y7 89T 68T 21T 76%
x16-y8 88T 70T 18T 79%
x16-y9 91T 69T 22T 75%
x16-y10 86T 72T 14T 83%
x16-y11 94T 70T 24T 74%
x16-y12 94T 71T 23T 75%
x16-y13 91T 71T 20T 78%
x16-y14 88T 72T 16T 81%
x16-y15 90T 65T 25T 72%
x16-y16 89T 69T 20T 77%
x16-y17 94T 65T 29T 69%
x16-y18 89T 64T 25T 71%
x16-y19 85T 68T 17T 80%
x16-y20 88T 70T 18T 79%
x16-y21 89T 73T 16T 82%
x16-y22 93T 69T 24T 74%
x16-y23 92T 73T 19T 79%
x16-y24 87T 71T 16T 81%
x17-y0 86T 69T 17T 80%
x17-y1 88T 70T 18T 79%
x17-y2 87T 71T 16T 81%
x17-y3 509T 495T 14T 97%
x17-y4 91T 64T 27T 70%
x17-y5 86T 66T 20T 76%
x17-y6 92T 66T 26T 71%
x17-y7 90T 70T 20T 77%
x17-y8 89T 72T 17T 80%
x17-y9 91T 71T 20T 78%
x17-y10 88T 66T 22T 75%
x17-y11 88T 64T 24T 72%
x17-y12 85T 67T 18T 78%
x17-y13 93T 70T 23T 75%
x17-y14 93T 66T 27T 70%
x17-y15 91T 66T 25T 72%
x17-y16 89T 67T 22T 75%
x17-y17 92T 70T 22T 76%
x17-y18 90T 73T 17T 81%
x17-y19 89T 71T 18T 79%
x17-y20 90T 67T 23T 74%
x17-y21 90T 73T 17T 81%
x17-y22 89T 68T 21T 76%
x17-y23 88T 70T 18T 79%
x17-y24 91T 73T 18T 80%
x18-y0 94T 73T 21T 77%
x18-y1 88T 64T 24T 72%
x18-y2 94T 69T 25T 73%
x18-y3 510T 496T 14T 97%
x18-y4 94T 65T 29T 69%
x18-y5 92T 69T 23T 75%
x18-y6 94T 70T 24T 74%
x18-y7 86T 69T 17T 80%
x18-y8 85T 70T 15T 82%
x18-y9 85T 67T 18T 78%
x18-y10 93T 67T 26T 72%
x18-y11 92T 66T 26T 71%
x18-y12 88T 64T 24T 72%
x18-y13 85T 68T 17T 80%
x18-y14 88T 71T 17T 80%
x18-y15 91T 69T 22T 75%
x18-y16 86T 68T 18T 79%
x18-y17 88T 66T 22T 75%
x18-y18 90T 64T 26T 71%
x18-y19 89T 67T 22T 75%
x18-y20 91T 68T 23T 74%
x18-y21 90T 65T 25T 72%
x18-y22 85T 65T 20T 76%
x18-y23 94T 73T 21T 77%
x18-y24 87T 70T 17T 80%
x19-y0 90T 73T 17T 81%
x19-y1 86T 68T 18T 79%
x19-y2 91T 65T 26T 71%
x19-y3 504T 497T 7T 98%
x19-y4 87T 64T 23T 73%
x19-y5 92T 68T 24T 73%
x19-y6 93T 0T 93T 0%
x19-y7 88T 68T 20T 77%
x19-y8 87T 67T 20T 77%
x19-y9 93T 64T 29T 68%
x19-y10 85T 73T 12T 85%
x19-y11 94T 66T 28T 70%
x19-y12 85T 69T 16T 81%
x19-y13 85T 72T 13T 84%
x19-y14 89T 69T 20T 77%
x19-y15 85T 64T 21T 75%
x19-y16 92T 72T 20T 78%
x19-y17 93T 70T 23T 75%
x19-y18 91T 65T 26T 71%
x19-y19 93T 72T 21T 77%
x19-y20 85T 70T 15T 82%
x19-y21 91T 71T 20T 78%
x19-y22 94T 67T 27T 71%
x19-y23 86T 69T 17T 80%
x19-y24 86T 66T 20T 76%
x20-y0 86T 70T 16T 81%
x20-y1 91T 69T 22T 75%
x20-y2 85T 66T 19T 77%
x20-y3 506T 494T 12T 97%
x20-y4 85T 67T 18T 78%
x20-y5 89T 70T 19T 78%
x20-y6 89T 65T 24T 73%
x20-y7 90T 69T 21T 76%
x20-y8 92T 69T 23T 75%
x20-y9 86T 72T 14T 83%
x20-y10 85T 64T 21T 75%
x20-y11 94T 68T 26T 72%
x20-y12 87T 73T 14T 83%
x20-y13 87T 69T 18T 79%
x20-y14 87T 64T 23T 73%
x20-y15 88T 72T 16T 81%
x20-y16 85T 69T 16T 81%
x20-y17 91T 71T 20T 78%
x20-y18 93T 72T 21T 77%
x20-y19 88T 69T 19T 78%
x20-y20 87T 68T 19T 78%
x20-y21 94T 64T 30T 68%
x20-y22 85T 64T 21T 75%
x20-y23 91T 66T 25T 72%
x20-y24 92T 67T 25T 72%
x21-y0 90T 71T 19T 78%
x21-y1 94T 65T 29T 69%
x21-y2 93T 64T 29T 68%
x21-y3 504T 491T 13T 97%
x21-y4 90T 70T 20T 77%
x21-y5 87T 66T 21T 75%
x21-y6 92T 73T 19T 79%
x21-y7 90T 71T 19T 78%
x21-y8 88T 66T 22T 75%
x21-y9 91T 65T 26T 71%
x21-y10 87T 72T 15T 82%
x21-y11 85T 65T 20T 76%
x21-y12 88T 69T 19T 78%
x21-y13 92T 73T 19T 79%
x21-y14 93T 66T 27T 70%
x21-y15 85T 68T 17T 80%
x21-y16 94T 73T 21T 77%
x21-y17 94T 64T 30T 68%
x21-y18 85T 68T 17T 80%
x21-y19 91T 70T 21T 76%
x21-y20 92T 73T 19T 79%
x21-y21 89T 65T 24T 73%
x21-y22 86T 70T 16T 81%
x21-y23 87T 73T 14T 83%
x21-y24 86T 64T 22T 74%
x22-y0 93T 67T 26T 72%
x22-y1 85T 66T 19T 77%
x22-y2 91T 69T 22T 75%
x22-y3 507T 492T 15T 97%
x22-y4 87T 66T 21T 75%
x22-y5 85T 65T 20T 76%
x22-y6 85T 67T 18T 78%
x22-y7 89T 72T 17T 80%
x22-y8 93T 69T 24T 74%
x22-y9 91T 67T 24T 73%
x22-y10 94T 70T 24T 74%
x22-y11 88T 65T 23T 73%
x22-y12 93T 65T 28T 69%
x22-y13 86T 66T 20T 76%
x22-y14 90T 64T 26T 71%
x22-y15 91T 68T 23T 74%
x22-y16 92T 66T 26T 71%
x22-y17 90T 69T 21T 76%
x22-y18 92T 67T 25T 72%
x22-y19 93T 71T 22T 76%
x22-y20 86T 69T 17T 80%
x22-y21 92T 70T 22T 76%
x22-y22 88T 73T 15T 82%
x22-y23 88T 72T 16T 81%
x22-y24 88T 67T 21T 76%
x23-y0 88T 66T 22T 75%
x23-y1 94T 66T 28T 70%
x23-y2 90T 67T 23T 74%
x23-y3 509T 494T 15T 97%
x23-y4 92T 72T 20T 78%
x23-y5 89T 72T 17T 80%
x23-y6 94T 73T 21T 77%
x23-y7 92T 64T 28T 69%
x23-y8 90T 65T 25T 72%
x23-y9 91T 67T 24T 73%
x23-y10 93T 65T 28T 69%
x23-y11 92T 66T 26T 71%
x23-y12 88T 72T 16T 81%
x23-y13 91T 66T 25T 72%
x23-y14 94T 67T 27T 71%
x23-y15 90T 72T 18T 80%
x23-y16 94T 66T 28T 70%
x23-y17 87T 73T 14T 83%
x23-y18 88T 66T 22T 75%
x23-y19 90T 69T 21T 76%
x23-y20 91T 64T 27T 70%
x23-y21 89T 64T 25T 71%
x23-y22 93T 64T 29T 68%
x23-y23 94T 71T 23T 75%
x23-y24 92T 70T 22T 76%
x24-y0 91T 70T 21T 76%
x24-y1 92T 70T 22T 76%
x24-y2 90T 70T 20T 77%
x24-y3 503T 493T 10T 98%
x24-y4 93T 64T 29T 68%
x24-y5 85T 70T 15T 82%
x24-y6 87T 71T 16T 81%
x24-y7 89T 72T 17T 80%
x24-y8 88T 72T 16T 81%
x24-y9 90T 68T 22T 75%
x24-y10 85T 67T 18T 78%
x24-y11 91T 67T 24T 73%
x24-y12 89T 71T 18T 79%
x24-y13 90T 73T 17T 81%
x24-y14 94T 68T 26T 72%
x24-y15 87T 67T 20T 77%
x24-y16 89T 68T 21T 76%
x24-y17 92T 72T 20T 78%
x24-y18 85T 72T 13T 84%
x24-y19 87T 72T 15T 82%
x24-y20 89T 66T 23T 74%
x24-y21 89T 72T 17T 80%
x24-y22 86T 71T 15T 82%
x24-y23 89T 67T 22T 75%
x24-y24 88T 66T 22T 75%
x25-y0 88T 69T 19T 78%
x25-y1 90T 68T 22T 75%
x25-y2 85T 72T 13T 84%
x25-y3 507T 499T 8T 98%
x25-y4 92T 69T 23T 75%
x25-y5 88T 73T 15T 82%
x25-y6 91T 64T 27T 70%
x25-y7 89T 66T 23T 74%
x25-y8 92T 72T 20T 78%
x25-y9 91T 65T 26T 71%
x25-y10 86T 65T 21T 75%
x25-y11 90T 66T 24T 73%
x25-y12 85T 68T 17T 80%
x25-y13 89T 65T 24T 73%
x25-y14 93T 65T 28T 69%
x25-y15 87T 68T 19T 78%
x25-y16 92T 73T 19T 79%
x25-y17 92T 72T 20T 78%
x25-y18 94T 69T 25T 73%
x25-y19 94T 71T 23T 75%
x25-y20 91T 70T 21T 76%
x25-y21 93T 67T 26T 72%
x25-y22 91T 64T 27T 70%
x25-y23 94T 71T 23T 75%
x25-y24 94T 70T 24T 74%
x26-y0 86T 71T 15T 82%
x26-y1 93T 69T 24T 74%
x26-y2 87T 71T 16T 81%
x26-y3 508T 491T 17T 96%
x26-y4 91T 73T 18T 80%
x26-y5 90T 67T 23T 74%
x26-y6 91T 73T 18T 80%
x26-y7 92T 72T 20T 78%
x26-y8 88T 69T 19T 78%
x26-y9 87T 72T 15T 82%
x26-y10 91T 69T 22T 75%
x26-y11 86T 72T 14T 83%
x26-y12 85T 71T 14T 83%
x26-y13 88T 73T 15T 82%
x26-y14 92T 64T 28T 69%
x26-y15 91T 70T 21T 76%
x26-y16 87T 72T 15T 82%
x26-y17 86T 67T 19T 77%
x26-y18 94T 72T 22T 76%
x26-y19 85T 66T 19T 77%
x26-y20 87T 65T 22T 74%
x26-y21 90T 66T 24T 73%
x26-y22 87T 66T 21T 75%
x26-y23 85T 72T 13T 84%
x26-y24 91T 70T 21T 76%
x27-y0 85T 73T 12T 85%
x27-y1 90T 72T 18T 80%
x27-y2 92T 64T 28T 69%
x27-y3 504T 495T 9T 98%
x27-y4 89T 69T 20T 77%
x27-y5 86T 69T 17T 80%
x27-y6 93T 71T 22T 76%
x27-y7 86T 65T 21T 75%
x27-y8 91T 65T 26T 71%
x27-y9 94T 64T 30T 68%
x27-y10 85T 68T 17T 80%
x27-y11 92T 67T 25T 72%
x27-y12 87T 67T 20T 77%
x27-y13 85T 68T 17T 80%
x27-y14 87T 69T 18T 79%
x27-y15 86T 65T 21T 75%
x27-y16 90T 67T 23T 74%
x27-y17 91T 71T 20T 78%
x27-y18 91T 73T 18T 80%
x27-y19 91T 72T 19T 79%
x27-y20 90T 65T 25T 72%
x27-y21 94T 66T 28T 70%
x27-y22 94T 66T 28T 70%
x27-y23 90T 64T 26T 71%
x27-y24 85T 68T 17T 80%
x28-y0 92T 71T 21T 77%
x28-y1 86T 64T 22T 74%
x28-y2 88T 71T 17T 80%
x28-y3 508T 491T 17T 96%
x28-y4 90T 65T 25T 72%
x28-y5 90T 69T 21T 76%
x28-y6 88T 71T 17T 80%
x28-y7 91T 69T 22T 75%
x28-y8 91T 64T 27T 70%
x28-y9 91T 64T 27T 70%
x28-y10 87T 65T 22T 74%
x28-y11 89T 69T 20T 77%
x28-y12 90T 64T 26T 71%
x28-y13 94T 67T 27T 71%
x28-y14 87T 65T 22T 74%
x28-y15 94T 65T 29T 69%
x28-y16 85T 64T 21T 75%
x28-y17 85T 64T 21T 75%
x28-y18 92T 66T 26T 71%
x28-y19 90T 72T 18T 80%
x28-y20 94T 69T 25T 73%
x28-y21 93T 71T 22T 76%
x28-y22 85T 70T 15T 82%
x28-y23 89T 68T 21T 76%
x28-y24 94T 66T 28T 70%
x29-y0 92T 69T 23T 75%
x29-y1 91T 71T 20T 78%
x29-y2 91T 65T 26T 71%
x29-y3 504T 491T 13T 97%
x29-y4 89T 70T 19T 78%
x29-y5 90T 68T 22T 75%
x29-y6 88T 72T 16T 81%
x29-y7 91T 68T 23T 74%
x29-y8 85T 65T 20T 76%
x29-y9 91T 69T 22T 75%
x29-y10 87T 65T 22T 74%
x29-y11 91T 64T 27T 70%
x29-y12 85T 67T 18T 78%
x29-y13 87T 72T 15T 82%
x29-y14 94T 67T 27T 71%
x29-y15 91T 68T 23T 74%
x29-y16 90T 65T 25T 72%
x29-y17 91T 70T 21T 76%
x29-y18 89T 73T 16T 82%
x29-y19 85T 64T 21T 75%
x29-y20 93T 71T 22T 76%
x29-y21 93T 69T 24T 74%
x29-y22 93T 72T 21T 77%
x29-y23 93T 68T 25T 73%
x29-y24 94T 72T 22T 76%
x30-y0 87T 70T 17T 80%
x30-y1 94T 72T 22T 76%
x30-y2 88T 65T 23T 73%
x30-y3 501T 491T 10T 98%
x30-y4 87T 66T 21T 75%
x30-y5 94T 71T 23T 75%
x30-y6 91T 66T 25T 72%
x30-y7 88T 66T 22T 75%
x30-y8 94T 70T 24T 74%
x30-y9 86T 71T 15T 82%
x30-y10 86T 65T 21T 75%
x30-y11 85T 69T 16T 81%
x30-y12 92T 70T 22T 76%
x30-y13 85T 68T 17T 80%
x30-y14 93T 65T 28T 69%
x30-y15 85T 72T 13T 84%
x30-y16 91T 72T 19T 79%
x30-y17 86T 72T 14T 83%
x30-y18 89T 71T 18T 79%
x30-y19 88T 68T 20T 77%
x30-y20 94T 66T 28T 70%
x30-y21 88T 68T 20T 77%
x30-y22 90T 70T 20T 77%
x30-y23 92T 72T 20T 78%
x30-y24 92T 73T 19T 79%
x31-y0 87T 65T 22T 74%
x31-y1 90T 73T 17T 81%
x31-y2 90T 68T 22T 75%
x31-y3 509T 499T 10T 98%
x31-y4 92T 71T 21T 77%
x31-y5 93T 64T 29T 68%
x31-y6 86T 73T 13T 84%
x31-y7 89T 66T 23T 74%
x31-y8 94T 71T 23T 75%
x31-y9 92T 71T 21T 77%
x31-y10 86T 68T 18T 79%
x31-y11 87T 69T 18T 79%
x31-y12 85T 71T 14T 83%
x31-y13 85T 65T 20T 76%
x31-y14 93T 68T 25T 73%
x31-y15 89T 71T 18T 79%
x31-y16 92T 70T 22T 76%
x31-y17 87T 70T 17T 80%
x31-y18 90T 68T 22T 75%
x31-y19 91T 67T 24T 73%
x31-y20 94T 68T 26T 72%
x31-y21 91T 70T 21T 76%
x31-y22 91T 65T 26T 71%
x31-y23 85T 69T 16T 81%
x31-y24 90T 72T 18T 80%
x32-y0 86T 66T 20T 76%
x32-y1 91T 71T 20T 78%
x32-y2 86T 68T 18T 79%
x32-y3 503T 498T 5T 99%
x32-y4 89T 65T 24T 73%
x32-y5 90T 72T 18T 80%
x32-y6 91T 71T 20T 78%
x32-y7 89T 69T 20T 77%
x32-y8 94T 64T 30T 68%
x32-y9 89T 67T 22T 75%
x32-y10 92T 64T 28T 69%
x32-y11 85T 69T 16T 81%
x32-y12 92T 69T 23T 75%
x32-y13 86T 69T 17T 80%
x32-y14 94T 70T 24T 74%
x32-y15 87T 67T 20T 77%
x32-y16 92T 69T 23T 75%
x32-y17 89T 66T 23T 74%
x32-y18 94T 70T 24T 74%
x32-y19 89T 71T 18T 79%
x32-y20 85T 68T 17T 80%
x32-y21 85T 73T 12T 85%
x32-y22 92T 71T 21T 77%
x32-y23 85T 70T 15T 82%
x32-y24 88T 65T 23T 73%
x33-y0 88T 69T 19T 78%
x33-y1 88T 66T 22T 75%
x33-y2 90T 73T 17T 81%
x33-y3 506T 492T 14T 97%
x33-y4 90T 67T 23T 74%
x33-y5 89T 71T 18T 79%
x33-y6 92T 73T 19T 79%
x33-y7 85T 68T 17T 80%
x33-y8 91T 66T 25T 72%
x33-y9 92T 71T 21T 77%
x33-y10 91T 70T 21T 76%
x33-y11 93T 71T 22T 76%
x33-y12 91T 69T 22T 75%
x33-y13 92T 66T 26T 71%
x33-y14 87T 73T 14T 83%
x33-y15 93T 71T 22T 76%
x33-y16 94T 69T 25T 73%
x33-y17 91T 72T 19T 79%
x33-y18 86T 67T 19T 77%
x33-y19 87T 65T 22T 74%
x33-y20 86T 68T 18T 79%
x33-y21 88T 64T 24T 72%
x33-y22 92T 70T 22T 76%
x33-y23 87T 71T 16T 81%
x33-y24 92T 73T 19T 79%
x34-y0 88T 73T 15T 82%
x34-y1 91T 72T 19T 79%
x34-y2 89T 69T 20T 77%
x34-y3 510T 499T 11T 97%
x34-y4 92T 70T 22T 76%
x34-y5 86T 71T 15T 82%
x34-y6 93T 68T 25T 73%
x34-y7 89T 69T 20T 77%
x34-y8 91T 73T 18T 80%
x34-y9 85T 69T 16T 81%
x34-y10 94T 71T 23T 75%
x34-y11 85T 71T 14T 83%
x34-y12 92T 72T 20T 78%
x34-y13 92T 66T 26T 71%
x34-y14 94T 66T 28T 70%
x34-y15 93T 69T 24T 74%
x34-y16 94T 67T 27T 71%
x34-y17 89T 73T 16T 82%
x34-y18 89T 64T 25T 71%
x34-y19 93T 66T 27T 70%
x34-y20 93T 73T 20T 78%
x34-y21 91T 68T 23T 74%
x34-y22 94T 68T 26T 72%
x34-y23 91T 64T 27T 70%
x34-y24 91T 64T 27T 70%
x35-y0 87T 72T 15T 82%
x35-y1 89T 71T 18T 79%
x35-y2 85T 70T 15T 82%
x35-y3 510T 493T 17T 96%
x35-y4 86T 72T 14T 83%
x35-y5 91T 65T 26T 71%
x35-y6 93T 69T 24T 74%
x35-y7 93T 64T 29T 68%
x35-y8 87T 69T 18T 79%
x35-y9 93T 64T 29T 68%
x35-y10 85T 69T 16T 81%
x35-y11 90T 67T 23T 74%
x35-y12 93T 73T 20T 78%
x35-y13 85T 73T 12T 85%
x35-y14 85T 73T 12T 85%
x35-y15 86T 71T 15T 82%
x35-y16 90T 64T 26T 71%
x35-y17 90T 65T 25T 72%
x35-y18 93T 70T 23T 75%
x35-y19 92T 72T 20T 78%
x35-y20 86T 71T 15T 82%
x35-y21 86T 68T 18T 79%
x35-y22 88T 68T 20T 77%
x35-y23 89T 69T 20T 77%
x35-y24 93T 70T 23T 75%
x36-y0 85T 67T 18T 78%
x36-y1 91T 72T 19T 79%
x36-y2 90T 73T 17T 81%
x36-y3 502T 499T 3T 99%
x36-y4 89T 70T 19T 78%
x36-y5 85T 71T 14T 83%
x36-y6 94T 70T 24T 74%
x36-y7 88T 72T 16T 81%
x36-y8 90T 70T 20T 77%
x36-y9 88T 69T 19T 78%
x36-y10 90T 71T 19T 78%
x36-y11 91T 68T 23T 74%
x36-y12 89T 71T 18T 79%
x36-y13 94T 67T 27T 71%
x36-y14 91T 65T 26T 71%
x36-y15 85T 64T 21T 75%
x36-y16 85T 67T 18T 78%
x36-y17 89T 66T 23T 74%
x36-y18 89T 72T 17T 80%
x36-y19 93T 69T 24T 74%
x36-y20 89T 73T 16T 82%
x36-y21 91T 72T 19T 79%
x36-y22 88T 71T 17T 80%
x36-y23 93T 68T 25T 73%
x36-y24 91T 64T 27T 70%

)x";
