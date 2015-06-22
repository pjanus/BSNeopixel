#include <BSNeopixel.h>

#include <avr/power.h>

BSNeopixel bs = BSNeopixel();
uint32_t RED, GREEN, BLUE, BLACK;


void setup() {
    bs.begin();
    bs.show();
    Serial.begin(9600);

    RED = bs.Color(128,0,0);
    GREEN = bs.Color(0,128,0);
    BLUE = bs.Color(0,0,128);
    BLACK = bs.Color(0,0,0);
    randomSeed(analogRead(0));
}

void loop() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            bs.setShelfColor(i, j, BLACK);
        }
    }

    byte rows[5];
    int read = Serial.readBytes(rows, 5);
    for (int row = 0; row < 5; row++) {
        bs.setRowColor(row, rows[row]+1, BLUE);
    }
    bs.show();
}