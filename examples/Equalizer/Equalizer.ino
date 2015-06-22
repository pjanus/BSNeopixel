#include <BSNeopixel.h>

#include <avr/power.h>

BSNeopixel bs = BSNeopixel();
uint32_t RED, GREEN, BLUE, BLACK, YELLOW;
uint32_t COLORS[5];

void setup() {
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

void loop() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            bs.setShelfColor(i, j, BLACK);
        }
    }

    byte rows[bs.dataBytes];
    int read = Serial.readBytes(rows, bs.dataBytes);
    if (read == 0)
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