#include <BSNeopixel.h>

#include <avr/power.h>

#include <BSNeopixel.h>
#include <Effect.h>

#include "Animation.h"

BSNeopixel bs = BSNeopixel();
uint32_t BACKGROUND_COLOR, ANIMATION_COLOR;

int animation_step = 0;
int number_of_steps;

byte data[BSNeopixel::dataBytes];

int rainbow_steps = 25 * 10;
enum effect_t {
  rainbow,
  animation,
};
effect_t current_effect = rainbow;
Effect *effect;

void setup() {  
    bs.begin();
    bs.show();
    Serial.begin(9600);

    BACKGROUND_COLOR = bs.Color(0, 128, 0);
    ANIMATION_COLOR = bs.Color(128, 0, 0);

    number_of_steps = sizeof(ANIMATION) / 5;
    effect = new Rainbow(bs);
    //randomSeed(analogRead(0));
}

void loop() {
  if (current_effect == rainbow) {
    effect->step(data);
    if (++animation_step == rainbow_steps) {
      current_effect = animation;
      animation_step = 0;
    }
    delay(0.1);
  } else {
    for (int i = 0; i < bs.shelfRows; i++)
        for (int j = 0; j < bs.shelfCols; j++) {
            bs.setShelfColor(i, j, BACKGROUND_COLOR);
            if ((ANIMATION[animation_step][j] >> i) & 1)
                bs.setShelfColor(i, j, ANIMATION_COLOR);
        }
    if (++animation_step == number_of_steps) {
      current_effect = rainbow;
      animation_step = 0;
    }
    delay(555);
  }
  
  bs.show();
}
