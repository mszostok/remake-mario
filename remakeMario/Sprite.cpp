#include "Sprite.h"
#include "Engine.h"


//==============================================
// Sprite
//==============================================

/**
	Konstruktor & destruktor
*/
Sprite::Sprite(SpriteConfigPattern sprite){
	_data = sprite;
};

Sprite::~Sprite(){
	
};

/**
	Metody publiczne
*/

void Sprite::setPattern(SpriteConfigPattern &sprite){
	_data = sprite;
};

void Sprite::update(vector<player::State> &state){
	if (state[player::Horizontal] == player::stayLeft || state[player::Horizontal] == player::stayRight){
		if (state[player::Vertical] == player::stand){
			_data._curFrame = 0;
			_data._frameCount = 0;
		}
		else if (state[player::Vertical] == player::jump){
			_data._curFrame = _data._maxFrame *_data._direction;
			_data._frameCount = 0;
		}
	}
	else{
		if (state[player::Vertical] == player::jump){
			_data._curFrame = _data._maxFrame *_data._direction;
			_data._frameCount = 0;
		}
		else
			update();
	}
		
}

void Sprite::update(){

	if (++(_data)._frameCount >= (_data)._frameDelay) {
		(_data)._curFrame += _data._direction;

		if (abs(_data._curFrame) >= _data._maxFrame)
			_data._curFrame = 0;

		_data._frameCount = 0;
	}
}

void Sprite::drawCurrentFrame(double x, double y){


	int fx = _data._posX + (_data._curFrame * _data._frameWidth) ;
	int fy = _data._posY;

	al_draw_bitmap_region(Engine::get().spriteDatabase()->getAtlas(), fx, fy, _data._frameWidth, _data._frameHeight,
		x, y, 0);
}


