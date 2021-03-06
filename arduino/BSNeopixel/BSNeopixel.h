#ifndef BSNEOPIXEL_H
#define BSNEOPIXEL_H

#include "Adafruit_NeoPixel.h"

class BSNeopixel
{
  public:
    BSNeopixel(uint8_t* p=NULL);
    ~BSNeopixel();
        
    void begin(void);
    void show(void); 
    void setShelfColor(uint8_t row, uint8_t col, uint32_t color);
    /* returns color of first pixel in the shelf */
    uint32_t getShelfColor(uint8_t row, uint8_t col);
    void setPixelColor(uint8_t r, uint8_t c, uint8_t p, uint32_t color);
    void setPixelColor(uint8_t r, uint8_t c, uint32_t color);
    void setRowHeight(uint8_t r, uint8_t h, uint32_t color);
    void setBrightness(uint8_t);
    void colorWipe(uint32_t color);
    void clear();

    uint8_t getRows() { return shelfRows; }
    uint8_t getCols() { return shelfCols; }

    static uint32_t
      Color(uint8_t r, uint8_t g, uint8_t b);
    static uint32_t
      Color(uint8_t rgb[]);
  public:
    Adafruit_NeoPixel** strips;
    Adafruit_NeoPixel* strip;

    static const uint16_t shelfLEDs = 8;
    static const uint8_t
        shelfRows = 5,
        shelfCols = 5,
        dataBytes = 8;
    static uint8_t pins[5];
};

#endif
