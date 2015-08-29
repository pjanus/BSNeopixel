#include <BSNeopixel.h>

#include <avr/power.h>

#include "Animation.h"

BSNeopixel bs = BSNeopixel();
uint32_t BACKGROUND_COLOR, ANIMATION_COLOR;

int animation_setep = 0;
int number_of_steps;

byte data[BSNeopixel::dataBytes];

void setup() {  
    bs.begin();
    bs.show();
    Serial.begin(9600);

    BACKGROUND_COLOR = bs.Color(0, 128, 0);
    ANIMATION_COLOR = bs.Color(128, 0, 0);

    number_of_steps = sizeof(ANIMATION) / 5;
    //randomSeed(analogRead(0));
}

void loop() {
    /*
    int read = Serial.readBytes((char*)data, bs.dataBytes);
    if (read == 0)
      return;
    */
    data[5] = 1;

    if (data[5])
        for (int i = 0; i < bs.shelfRows; i++)
            for (int j = 0; j < bs.shelfCols; j++) {
                bs.setShelfColor(i, j, BACKGROUND_COLOR);
                if ((ANIMATION[animation_setep][j] >> i) & 1)
                    bs.setShelfColor(i, j, ANIMATION_COLOR);
            }
    ++animation_setep %= number_of_steps;
    
    bs.show();
    delay(555);
}
