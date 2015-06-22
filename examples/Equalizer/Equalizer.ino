#include <BSNeopixel.h>

#include <avr/power.h>

BSNeopixel bs = BSNeopixel();
uint32_t RED, GREEN, BLUE, BLACK;
uint32_t COLORS[5];

void setup() {
    bs.begin();
    bs.show();
    Serial.begin(9600);
    Serial.setTimeout(0);

    RED = bs.Color(128,0,0);
    GREEN = bs.Color(0,128,0);
    BLUE = bs.Color(0,0,128);
    BLACK = bs.Color(0,0,0);
    
    COLORS[0] = bs.Color(0, 0, 128),
    COLORS[1] = bs.Color(0, 32, 96),
    COLORS[2] = bs.Color(0, 64, 64),
    COLORS[3] = bs.Color(0, 96, 32),
    COLORS[4] = bs.Color(0, 128, 0);
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
    if (read == 0)
      return;
    Serial.print(read);
    Serial.println();
    Serial.write(rows, 5);
    Serial.println();
    for (int row = 0; row < 5; row++) {
        bs.setRowColor(row, rows[row]+1, COLORS[row]);
    }
    bs.show();
}