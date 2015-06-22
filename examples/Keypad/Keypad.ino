#include <Keypad.h>
#include <BSNeopixel.h>

#include <avr/power.h>

BSNeopixel bs = BSNeopixel();
uint32_t RED, GREEN, BLUE, BLACK, YELLOW;
uint32_t COLORS[5];

void equalizerSetup() {
    bs.begin();
    bs.show();
    Serial.begin(9600);
    Serial.setTimeout(0);

    RED = bs.Color(128,0,0);
    GREEN = bs.Color(0,128,0);
    BLUE = bs.Color(0,0,128);
    BLACK = bs.Color(0,0,0);
    YELLOW = bs.Color(128, 128, 0);

    COLORS[0] = bs.Color(0, 0, 128),
    COLORS[1] = bs.Color(0, 32, 96),
    COLORS[2] = bs.Color(0, 64, 64),
    COLORS[3] = bs.Color(0, 96, 32),
    COLORS[4] = bs.Color(0, 128, 0);
    randomSeed(analogRead(0));
}

void equalizerLoop() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            bs.setShelfColor(i, j, BLACK);
        }
    }

    byte rows[bs.dataBytes];
    int read = Serial.readBytes(rows, bs.dataBytes);
    
    if (read != bs.dataBytes)
      return;

    // for (int row = 0; row < 5; row++) {
    //     bs.setRowHeight(row, rows[row]+1, COLORS[row]);
    // }

    for (int row = 0; row < 5; row++) {
        for (int i = 0; i < rows[row]+1; i++) {
            // tricolors(row, i);
            gradient(row, i);
        }
    }

    bs.show();
}

void tricolors(int row, int i)
{
    uint32_t color = BLUE;
    if (i > 20) color = YELLOW;
    if (i > 31) color = RED;
    bs.setPixelColor(row, i, color);
}

void gradient(int row, int i)
{
    uint8_t red = map(i, 0, 39, 0, 128);
    uint8_t green = map(i, 0, 39, 128, 0);
    bs.setPixelColor(row, i, bs.Color(red, green, 0));
}

const uint32_t MAX_DOTS = 5;
byte dots[MAX_DOTS];


void setRandomDot(BSNeopixel *bs)
{
    int col = random(5);
    int row = random(5);
    bs->setShelfColor(row, col, RED);
}

int countDotsNumber(byte *frequences)
{
    int sum = 0;
    for (int i=0; i < 5 ; i++)
    {
        sum += frequences[i];
    }
    return sum / (39 * 5 / MAX_DOTS) + 1;
}

void dotsLoop() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            bs.setShelfColor(i, j, GREEN);
        }
    }

    byte rows[bs.dataBytes];
    int read = Serial.readBytes((char*)rows, bs.dataBytes);
    if (read != bs.dataBytes)
      return;

    if (rows[5]) {
        int number_of_dots = countDotsNumber(rows);
        for (int i=0; i < number_of_dots; i++) {
            setRandomDot(&bs);
        }
        bs.show(); delay(500);
    }
}

void dotsSetup() {
    bs.begin();
    bs.show();
    Serial.begin(9600);

    RED = bs.Color(128,0,0);
    GREEN = bs.Color(0,128,0);
    BLUE = bs.Color(0,0,128);
    randomSeed(analogRead(0));
}

const byte rows = 4; //four rows
const byte cols = 3; //three columns
char keys[rows][cols] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};
char mode = '1';
    
byte rowPins[rows] = {15, 14, 16, 10}; //connect to the row pinouts of the keypad
byte colPins[cols] = {2, 3, 4}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

void setup() {
    equalizerSetup();
    dotsSetup();
}

void loop() {
    char key = keypad.getKey();

    if (key != NO_KEY) {
        Serial.println(key);
        mode = key;
    }

    switch (mode) {
        case '1':
            equalizerLoop();
            break;
        case '2':
            dotsLoop();
            break;
    }
}
