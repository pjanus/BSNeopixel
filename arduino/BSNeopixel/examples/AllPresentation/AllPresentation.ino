#include <BSNeopixel.h>

#include <avr/power.h>

#include <BSNeopixel.h>
#include <Effect.h>

BSNeopixel bs = BSNeopixel();

int current_animation_no = 0;
int animations_no;

uint32_t last_time_changed;
int duration_time_ms =90 * 1000;

uint8_t data[1];

Effect **effects = NULL;
Effect *current_effect = NULL;

void setup() {  
  bs.begin();

  animations_no = get_all_effects(bs, &effects);
  current_effect = effects[0];
  last_time_changed = millis();
}

void loop() {
  current_effect->step(data);

  if (millis() - last_time_changed > duration_time_ms) {
    last_time_changed = millis();
    ++current_animation_no %= animations_no;
    current_effect = effects[current_animation_no];
  };
  delay(20);
}