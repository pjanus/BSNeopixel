#include <avr/power.h>

#include <BSNeopixel.h>
#include <Effect.h>

BSNeopixel bs = BSNeopixel();
Effect *effect;


void setup() {
    bs.begin();
    bs.show();
    Serial.begin(9600);
    float fps = 20; /* 10 - slow, 20 - quite slow, 50 - quite fast, 200 - very fast */
    uint16_t hue = 0; /* hue (degree value of color in hvs system) 0 - red */
    uint8_t saturation = 255; /* saturation lvl in hsv system (color intensity 0-255) */
    effect = new Blur(bs, fps, hue, saturation);
}

void loop() {
    byte data[bs.dataBytes];
    effect->step(data);
    delay(30);
}