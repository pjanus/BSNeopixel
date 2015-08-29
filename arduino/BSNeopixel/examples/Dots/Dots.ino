#include <avr/power.h>

#include <BSNeopixel.h>
#include <Effect.h>

BSNeopixel bs = BSNeopixel();
Effect *effect;


void setup() {
    bs.begin();
    bs.show();
    Serial.begin(9600);
    effect = new Dots(bs);
}

void loop() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            bs.setShelfColor(i, j, effect->GREEN);
        }
    }

    byte data[bs.dataBytes];
    int read = Serial.readBytes((char*)data, bs.dataBytes);
    if (read == 0)
      return;

    if (data[5])
        effect->step(data);
}