#include <BSNeopixel.h>

#include <avr/power.h>

BSNeopixel bs = BSNeopixel();
uint32_t RED, GREEN, BLUE;


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

	int col = random(5);
	int row = random(5);
	bs.setShelfColor(row, col, RED);
	bs.show(); delay(500);
}