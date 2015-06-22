#ifndef EFFECT_H
#define EFFECT_H

#include <BSNeopixel.h>

class Effect
{
protected:
	uint32_t RED, GREEN, BLUE, BLACK, YELLOW;
	BSNeopixel bs;
public:
	virtual void step(uint8_t data[]) = 0;
	Effect (BSNeopixel &bs)
	: bs(bs)
	{
	    RED = bs.Color(128,0,0);
	    GREEN = bs.Color(0,128,0);
	    BLUE = bs.Color(0,0,128);
	    BLACK = bs.Color(0,0,0);
	    YELLOW = bs.Color(128, 128, 0);
	    
	}
	virtual ~Effect () {}
};

class Equalizer: public Effect
{
private:
	uint32_t COLORS[5];
public:
	Equalizer(BSNeopixel &bs)
	: Effect(bs)
	{

	    COLORS[0] = bs.Color(0, 0, 128),
	    COLORS[1] = bs.Color(0, 32, 96),
	    COLORS[2] = bs.Color(0, 64, 64),
	    COLORS[3] = bs.Color(0, 96, 32),
	    COLORS[4] = bs.Color(0, 128, 0);
	}

	void step(uint8_t data[]);
	void tricolors(int row, int i);
	void gradient(int row, int i);
};

class Rainbow: public Effect
{
    public:
    Rainbow(BSNeopixel& bs) : Effect(bs) {}

    void step(uint8_t data[]);
    private:

    uint32_t hsvToRgb(uint16_t h, uint8_t s, uint8_t v);
};

#endif
