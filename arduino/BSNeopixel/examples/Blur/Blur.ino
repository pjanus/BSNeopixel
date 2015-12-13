#include <avr/power.h>

#include <BSNeopixel.h>
#include <Effect.h>

BSNeopixel bs = BSNeopixel();
Effect *effect;


void setup() {
    bs.begin();
    bs.show();
    Serial.begin(9600);
    effect = new Blur(bs, 10, 0);
}

void loop() {
    byte data[bs.dataBytes];
    effect->step(data);
    delay(30);
}