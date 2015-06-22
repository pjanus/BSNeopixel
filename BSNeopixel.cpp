#include "BSNeopixel.h"

BSNeopixel::BSNeopixel(uint8_t* p)
{
  if (p != NULL) {
    for (int i = 0; i < shelfRows; i++) {
      pins[i] = p[i];
    }
  }

  strips = new Adafruit_NeoPixel*[shelfRows];
  for (int i = 0; i < shelfRows; i++) {
    strips[i] = new Adafruit_NeoPixel(shelfCols * shelfLEDs, pins[i], NEO_GRB + NEO_KHZ800);
  }
}

BSNeopixel::~BSNeopixel()
{
	for (int i = 0; i < shelfRows; i++) {
		delete strips[i];
	}
	delete[] strips;
}

void BSNeopixel::begin(void)
{
        Serial.println("Begin");
	for (int i = 0; i < shelfRows; i++) {
                Serial.println(i);
		strips[i]->begin();
	}
}

void BSNeopixel::show(void)
{
    Serial.println("Show");
	for (int i = 0; i < shelfRows; i++) {
                Serial.println(i);
		strips[i]->show();
	}
}

void BSNeopixel::setShelfColor(uint8_t row, uint8_t col, uint32_t color)
{
	uint16_t firstLED = col * shelfLEDs;
	for (uint16_t n = firstLED; n < firstLED + shelfLEDs; n++) {
                Serial.print("Setting pixel ");
                Serial.print(n);
                Serial.print(" on strip ");
                Serial.println(row);
		strips[row]->setPixelColor(n, color);
	}
}

void BSNeopixel::setPixelColor(uint8_t r, uint8_t c, uint8_t p, uint32_t color)
{
	strips[row]->setPixelColor(c * shelfLEDs + p, color);
}

void BSNeopixel::setBrightness(uint8_t level)
{
	for (int i = 0; i < shelfRows; i++) {
		strips[i]->setBrightness(level);
	}
}

void BSNeopixel::clear()
{
	for (int i = 0; i < shelfRows; i++) {
		strips[i]->clear();
	}
}

uint32_t BSNeopixel::Color(uint8_t r, uint8_t g, uint8_t b)
{
	return Adafruit_NeoPixel::Color(r,g,b);
}
