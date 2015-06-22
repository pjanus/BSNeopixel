#include <avr/power.h>

#include <BSNeopixel.h>
#include <Effect.h>
#include <Keypad.h>

BSNeopixel bs = BSNeopixel();
const int EFFECTS_NUM = 3;
Effect *effects[EFFECTS_NUM];

const byte rows = 4; //four rows
const byte cols = 3; //three columns
char keys[rows][cols] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

byte rowPins[rows] = {15, 14, 16, 10}; //connect to the row pinouts of the keypad
byte colPins[cols] = {2, 3, 4}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

uint8_t effect = 0;

void setup() {
    bs.begin();
    bs.show();
    Serial.begin(9600);
    Serial.setTimeout(0);

    effects[0] = new Equalizer(bs);
    effects[1] = new Rainbow(bs);
    effects[2] = new Animation(bs);
}

void loop() {
    char key = keypad.getKey();

    if (key != NO_KEY && '1' <= key && key < '1' + EFFECTS_NUM) {
        Serial.println(key);
        effect = key - '1';
    }

    byte data[bs.dataBytes];
    int read = Serial.readBytes((char*)data, bs.dataBytes);
    if (read == 0)
      return;

    effects[effect]->step(data);
}
