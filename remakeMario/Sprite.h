#ifndef SPRITE_H
#define SPRITE_H

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

#include <string>
#include <map>
#include <vector>
#include <cmath>

#include "SpriteDatabase.h"


using namespace std;



//==============================================
// Sprite
//==============================================
class Sprite{

	SpriteConfigPattern _data;

public:

	Sprite(SpriteConfigPattern sprite);
	Sprite() {};
	~Sprite();

	void drawCurrentFrame(double x, double y);

	/* Settery */
	void setPattern(SpriteConfigPattern &sprite);

	/* Modyfikatory */
	void update(vector<player::State> &_state);		 // u¿ywana tylko dla obiektu klasy Player, u³atwia rysowanie spritów w zale¿noœci od stanu w jakim gracz siê znajduje
	void update();									// standardowe aktualizowanie obiektu klasy Sprite
	
};


#endif
