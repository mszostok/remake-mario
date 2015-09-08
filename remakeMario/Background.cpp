#include "Background.h"


/**
	konstruktor & destruktor
*/

Background::Background(){
	srand(time(NULL));

	init();
}
Background::~Background(){}



/**
	Metody publiczne
*/

void Background::init(){
	
	_displayWidth = al_get_display_width(al_get_current_display());

	//bg
	_bg._dirX = -1;
	_bg._velX = 0.3;

	_bg._width = 2000;

	_bg._x = 0;
	_bg._y = 0;


	//fg
	_fg._dirX = -1;
	_fg._velX = 0.3;

	_fg._width = 1239;

	_fg._x = 0;
	_fg._y = 35;
}

void Background::update(double velX){

	_bg._x += _bg._velX *  _bg._dirX;

	if (_bg._x + _bg._width <= 0) // jeœli bg wyszed³ ca³y za okno
		_bg._x = 0;				 // to od poczatku

	if(velX){
	_fg._x += _fg._velX  *  _fg._dirX * velX;

	if (_fg._x + _fg._width <= 0) // jeœli fg wyszed³ ca³y za okno
		_fg._x = 0;				 // to od poczatku
	}
}

void Background::draw(){

	al_draw_bitmap(Engine::get().spriteDatabase()->getBG(), _bg._x, _bg._y, 0);

	if (_bg._x + _bg._width < _displayWidth)
		al_draw_bitmap(Engine::get().spriteDatabase()->getBG(), _bg._x + _bg._width, _bg._y, 0);

	
	al_draw_bitmap(Engine::get().spriteDatabase()->getFG(), _fg._x, _fg._y, 0);

	if (_fg._x + _fg._width < _displayWidth)
		al_draw_bitmap(Engine::get().spriteDatabase()->getFG(), _fg._x + _fg._width, _fg._y, 0);

}

