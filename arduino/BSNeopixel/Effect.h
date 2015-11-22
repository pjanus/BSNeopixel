#ifndef EFFECT_H
#define EFFECT_H

#include <BSNeopixel.h>

class Effect
{
protected:
	BSNeopixel bs;
	int rows;
	int cols;
	int step_duration;
	uint32_t last_step_time;
	uint32_t hsvToRgb(uint16_t h, uint8_t s, uint8_t v);
	// set random color to every shelf
	uint32_t randomize();
	// detect if next step should be invoked
	//(step_duration elapsed from last succesfull invoke of step function)
	bool make_step();
public:
	virtual void step(uint8_t data[]) = 0;
	Effect (BSNeopixel &bs, float fps = 2)
	: bs(bs), step_duration(1000.0/fps)
	{
	    rows = bs.getRows();
	    cols = bs.getCols();

	    RED = bs.Color(128,0,0);
	    GREEN = bs.Color(0,128,0);
	    BLUE = bs.Color(0,0,128);
	    BLACK = bs.Color(0,0,0);
	    YELLOW = bs.Color(128, 128, 0);

	    last_step_time = -1;
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
    Rainbow(BSNeopixel& bs) : Effect(bs, fps) {}

    void step(uint8_t data[]);
    private:
    const int fps = 60;
};


/* animation */

class Animation: public Effect
{
    public:
    Animation(BSNeopixel& bs, float fps=1.66)
    : Effect(bs, fps), background_color(Effect::GREEN), animation_color(Effect::RED) {}

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


class Blur : public Effect
{
private:
    struct BlurState {
        bool rising;
        uint32_t min_brightness;
        uint32_t max_brightness;
    };
	struct BlurState bs_state[5][5];
public:
	Blur(BSNeopixel &bs)
	: Effect(bs)
	{
		randomSeed(analogRead(0));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            reset_shelf(i, j);
        }
    }
  }

  void reset_shelf(int i, int j);
	void step(uint8_t data[]);
};


class SpaceConsole : public Effect
{
private:
  int colors;
  int change_density;
public:
	SpaceConsole(BSNeopixel &bs, int fps = 50, int colors = 25, int change_density = 5)
	: Effect(bs, fps), colors(colors), change_density(change_density)
	{
		randomSeed(analogRead(0));
    randomize();
  }

	void step(uint8_t data[]);
};

/* returns array of effects with number of them */
int get_all_effects(BSNeopixel &bs, Effect*** effects);

#endif
