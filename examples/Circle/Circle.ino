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
        bs.show(); delay(500);
	circle(1, bs.Color(0,128,0));
        bs.show(); delay(500);
	circle(2, bs.Color(0,0,128));
        bs.show(); delay(500);
}

void circle(int l, int color)
{
	for (int c = l; c < bs.shelfRows-l-1; c++) {
		bs.setShelfColor(0, c, color);    
	}

	for (int r = l; r < bs.shelfRows-l-1; r++) {
		bs.setShelfColor(r, bs.shelfRows-1, color);
	}

	for (int c = bs.shelfRows-1; c > l; c--) {
		bs.setShelfColor(bs.shelfRows-1, c, color);
	}

	for (int r = bs.shelfRows-1; r > l; r--) {
		bs.setShelfColor(r, 0, color);
	}
}
