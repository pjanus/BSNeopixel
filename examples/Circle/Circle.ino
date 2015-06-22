#include <BSNeopixel.h>

#include <avr/power.h>

BSNeopixel bs = BSNeopixel();

void setup() {
    bs.begin();
    bs.show();
    Serial.begin(9600);
}

void loop()
{
    circle(0, bs.Color(128,0,0));
    bs.show(); delay(300);
    circle(1, bs.Color(0,128,0));
    bs.show(); delay(400);
    circle(2, bs.Color(0,0,128));
    bs.show(); delay(500);

    for (int i = 0; i < 5; i++) {
        bs.setShelfColor(0, i, bs.Color(128,0,0));
        bs.setShelfColor(4, i, bs.Color(128,0,0));
        bs.setShelfColor(i, 0, bs.Color(128,0,0));
        bs.setShelfColor(i, 4, bs.Color(128,0,0));
    }
    for (int i = 1; i < 4; i++) {
        bs.setShelfColor(1, i, bs.Color(0,128,0));
        bs.setShelfColor(3, i, bs.Color(0,128,0));
        bs.setShelfColor(i, 1, bs.Color(0,128,0));
        bs.setShelfColor(i, 3, bs.Color(0,128,0));
    }
    for (int i = 2; i < 3; i++) {
        bs.setShelfColor(2, i, bs.Color(0,0,128));
        bs.setShelfColor(2, i, bs.Color(0,0,128));
        bs.setShelfColor(i, 2, bs.Color(0,0,128));
        bs.setShelfColor(i, 2, bs.Color(0,0,128));
    }
    bs.show(); delay(500);
    // circle(0, bs.Color(0,0,128));
    // bs.show(); delay(300);
    // circle(1, bs.Color(0,128,0));
    // bs.show(); delay(400);
    // circle(2, bs.Color(128,0,0));
    // bs.show(); delay(500);
}

void circle(int ring, int color)
{
    for (int c = ring; c <= bs.shelfRows-ring-1; c++) {
        bs.setShelfColor(ring, c, color);    
    }

    for (int r = ring; r < bs.shelfRows-ring-1; r++) {
        bs.setShelfColor(r, bs.shelfRows-ring-1, color);
    }

    for (int c = bs.shelfRows-ring-1; c > ring; c--) {
        bs.setShelfColor(bs.shelfRows-ring-1, c, color);
    }

    for (int r = bs.shelfRows-ring-1; r > ring; r--) {
        bs.setShelfColor(r, ring, color);
    }
}