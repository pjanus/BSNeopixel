#include <avr/power.h>

#include <BSNeopixel.h>
#include <Effect.h>

BSNeopixel bs = BSNeopixel();
Effect *snake;

void setup() {
    bs.begin();
    bs.show();
    Serial.begin(9600);
    Serial.setTimeout(0);

    snake = new Snake(bs);
}

void loop() {

    byte data[bs.dataBytes];
    int read = Serial.readBytes((char*)data, bs.dataBytes);
    if (read == 0)
      return;

    snake->step(data);
}