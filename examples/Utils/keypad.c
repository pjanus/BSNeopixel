#include <Keypad.h>

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

void setup() {
    Serial.begin(9600);
}

void loop() {
    char key = keypad.getKey();

    if (key != NO_KEY) {
        Serial.println(key);
    }
}