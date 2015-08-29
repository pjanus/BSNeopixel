#include <BSNeopixel.h>

#include <avr/power.h>

BSNeopixel bs = BSNeopixel();
uint32_t RED, GREEN, BLUE;

const uint32_t MAX_DOTS = 5;
byte dots[MAX_DOTS];

int current_appearing, current_vanishing = 0;
uint8_t color[3] = {255, 0, 0};

void setup() {
    bs.begin();
    bs.show();
    Serial.begin(9600);

    RED = bs.Color(128,0,0);
    GREEN = bs.Color(0,128,0);
    BLUE = bs.Color(0,0,128);
    randomSeed(analogRead(0));
}

void loop() {
    int c;
    if (color[current_vanishing] == 0)
      ++current_vanishing %= 3;
    current_appearing = (current_vanishing + 1) % 3;
    
    color[current_appearing] += 5;
    color[current_vanishing] -= 5;

    for (int i = 0; i < bs.shelfRows; i++)
        for (int j = 0; j < bs.shelfCols; j++)
            bs.setShelfColor(i, j, bs.Color(color));
    bs.show();
    delay(50);
}