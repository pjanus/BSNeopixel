#include <BSNeopixel.h>

#include <avr/power.h>

BSNeopixel bs = BSNeopixel();
uint32_t RED, GREEN, BLUE;

const uint32_t MAX_DOTS = 5;
byte dots[MAX_DOTS];


void setRandomDot(BSNeopixel *bs)
{
    int col = random(5);
    int row = random(5);
    bs->setShelfColor(row, col, RED);
}

int countDotsNumber(byte *frequences)
{
    int sum = 0;
    for (int i=0; i < 5 ; i++)
    {
        sum += frequences[i];
    }
    return sum / (39 * 5 / MAX_DOTS) + 1;
}


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
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            bs.setShelfColor(i, j, GREEN);
        }
    }

    byte rows[bs.dataBytes];
    int read = Serial.readBytes((char*)rows, bs.dataBytes);
    if (read == 0)
      return;

    if (rows[5]) {
        int number_of_dots = countDotsNumber(rows);
        for (int i=0; i < rows[number_of_dots]; i++) {
            setRandomDot(&bs);
        }
        bs.show(); delay(500);
    }
}