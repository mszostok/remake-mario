#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <cmath>
#include <ctime>
#include <memory>

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

#include "Engine.h"
#include "GameObject.h"

struct BackgroundPattern{
	float _x;
	float _y;

	float _velX;
	int _dirX;

	int _width;
};


class Background : public GameObject {
	float _displayWidth;
	
	BackgroundPattern _bg;
	BackgroundPattern _fg;

	ALLEGRO_TIMER *_timer;

public:
	Background();
	~Background();

	void init();
	void draw();
	void update(double velX);
};

typedef std::shared_ptr < Background > BackgroundPtr;
#endif