#include <BSNeopixel.h>

#include <avr/power.h>

BSNeopixel bs = BSNeopixel();
uint32_t BACKGROUND_COLOR, ANIMATION_COLOR;

const int ANIMATION_STEPS = 2;
int animation_setep = 0;

byte data[BSNeopixel::dataBytes];

const uint8_t ANIMATION[ANIMATION_STEPS][BSNeopixel::shelfRows][BSNeopixel::shelfCols] = 
{
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
    {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    }
};

void setup() {
    bs.begin();
    bs.show();
    Serial.begin(9600);

    BACKGROUND_COLOR = bs.Color(0, 128, 0);
    ANIMATION_COLOR = bs.Color(128, 0, 0);

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
            for (int j = 0; j < bs.shelfCols; j++)
                if (ANIMATION[animation_setep][i][j])
                    bs.setShelfColor(i, j, ANIMATION_COLOR);
    ++animation_setep %= ANIMATION_STEPS;
    
    bs.show();
    delay(50);
}