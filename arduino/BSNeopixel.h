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
    void setPixelColor(uint8_t r, uint8_t c, uint8_t p, uint32_t color);
    void setRowColor(uint8_t r, uint8_t h, uint32_t color);
    void setBrightness(uint8_t);
    void clear();

    uint8_t getRows() { return shelfRows; }
    uint8_t getCols() { return shelfCols; }

    static uint32_t
      Color(uint8_t r, uint8_t g, uint8_t b);
  public:
    Adafruit_NeoPixel** strips;
    Adafruit_NeoPixel* strip;
    const uint16_t shelfLEDs = 8;
    const uint8_t
      shelfRows = 5,
      shelfCols = 5;
    uint8_t pins[5] = {5, 6, 7, 8, 9};
    
};

#endif
