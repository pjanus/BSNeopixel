#include <avr/power.h>

#include <BSNeopixel.h>
#include <Effect.h>

BSNeopixel bs = BSNeopixel();
Effect *equalizer;

void setup() {
    bs.begin();
    bs.show();
    Serial.begin(9600);
    Serial.setTimeout(0);

    equalizer = new Equalizer(bs);
}

void loop() {

    byte data[bs.dataBytes];
    int read = Serial.readBytes((char*)data, bs.dataBytes);
    if (read == 0)
      return;

    equalizer->step(data);
}