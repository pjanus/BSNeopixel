#include "Effect.h"
#include "Animation.h"



/* equalizer */

void Equalizer::step(uint8_t data[])
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            bs.setShelfColor(i, j, BLACK);
        }
    }

    for (int row = 0; row < 5; row++) {
        for (int i = 0; i < data[row]+1; i++) {
            // tricolors(row, i);
            gradient(row, i);
        }
    }

    bs.show();
}

void Equalizer::tricolors(int row, int i)
{
    uint32_t color = BLUE;
    if (i > 20) color = YELLOW;
    if (i > 31) color = RED; 
    bs.setPixelColor(row, i, color);
}

void Equalizer::gradient(int row, int i)
{
    uint8_t red = map(i, 0, 39, 0, 128);
    uint8_t green = map(i, 0, 39, 128, 0);
    bs.setPixelColor(row, i, bs.Color(red, green, 0));
}


/* rainbow */

void Rainbow::step(uint8_t data[]) {
    uint16_t time = millis() >> 2;
    uint8_t box = 0;

    for (int col = 0; col < 5; col++) {
        for (int row = 0; row < 5; row++) {
            byte x = (time >> 2) - (box << 3);
            uint32_t color = hsvToRgb((uint32_t)x * 359 / 256, 255, 255);

            bs.setShelfColor(row, col, color);
            box++;
        }
    }

    bs.show();
}


uint32_t Rainbow::hsvToRgb(uint16_t h, uint8_t s, uint8_t v)
{
    uint8_t f = (h % 60) * 255 / 60;
    uint8_t p = (255 - s) * (uint16_t)v / 255;
    uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t r = 0, g = 0, b = 0;
    switch((h / 60) % 6){
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
    }
    return bs.Color(r, g, b);
}


/* animation */

void Animation::step(uint8_t data[]) {
    uint32_t animation_step = (millis() / 500) % NUMBER_OF_STEPS;

    for (int i = 0; i < bs.shelfRows; i++)
        for (int j = 0; j < bs.shelfCols; j++) {
            bs.setShelfColor(i, j, background_color);
            if ((ANIMATION[animation_step][j] >> (BSNeopixel::shelfRows - i - 1)) & 1)
                bs.setShelfColor(i, j, animation_color);
        }

    bs.show();
}


/* dots */

void Dots::step(uint8_t data[])
{
    int number_of_dots = countDotsNumber(data);
    for (int i=0; i < number_of_dots; i++) {
        setRandomDot();
    }
    bs.show(); delay(500);
}

void Dots::setRandomDot()
{
    int col = random(bs.shelfCols);
    int row = random(bs.shelfRows);
    bs.setShelfColor(row, col, RED);
}

int Dots::countDotsNumber(uint8_t data[])
{
    int sum = 0;
    for (int i=0; i < 5 ; i++)
    {
        sum += data[i];
    }
    return sum / (39 * bs.shelfCols / MAX_DOTS) + 1;
}
