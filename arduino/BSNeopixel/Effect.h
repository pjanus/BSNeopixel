#ifndef EFFECT_H
#define EFFECT_H

#include <BSNeopixel.h>

class Effect
{
protected:
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

	uint32_t RED, GREEN, BLUE, BLACK, YELLOW;
};


/* equalizer */

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

/* rainbow */

class Rainbow: public Effect
{
    public:
    Rainbow(BSNeopixel& bs) : Effect(bs) {}

    void step(uint8_t data[]);
    private:

    uint32_t hsvToRgb(uint16_t h, uint8_t s, uint8_t v);
};


/* animation */

class Animation: public Effect
{
    public:
    Animation(BSNeopixel& bs) : Effect(bs), background_color(Effect::GREEN), animation_color(Effect::RED) {}

    void step(uint8_t data[]);

    private:
    uint32_t background_color, animation_color;
};


/* dots */

class Dots: public Effect
{
private:
	static const uint32_t MAX_DOTS = 5;
	void setRandomDot();
	int countDotsNumber(uint8_t data[]);
	uint32_t fgColor, bgColor;
public:
	Dots(BSNeopixel &bs)
	: Effect(bs)
	{
		bgColor = BLUE;
		fgColor = RED;
    	randomSeed(analogRead(0));
	}
	void step(uint8_t data[]);
};


class Snake : public Effect
{
private:
	static const int max_len = 5;
	int8_t snake_row[max_len];
	int8_t snake_col[max_len];

	void nextShelf(int8_t snake[]);
	void shift();
	void reset();
public:
	Snake(BSNeopixel &bs)
	: Effect(bs)
	{
		randomSeed(analogRead(0));
		reset();
	}

	void step(uint8_t data[]);
};
#endif
