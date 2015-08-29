#include <avr/power.h>

#include <BSNeopixel.h>
#include <Effect.h>

BSNeopixel bs = BSNeopixel();
Effect *effect;

void setup() {
    bs.begin();
    bs.show();
    Serial.begin(9600);
    Serial.setTimeout(0);

    effect = new Rainbow(bs);
}

void loop() {

    byte data[bs.dataBytes];
    int read = Serial.readBytes((char*)data, bs.dataBytes);
    if (read == 0)
      return;

    effect->step(data);
}
