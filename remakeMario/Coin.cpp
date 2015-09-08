#include "Coin.h"
#include "Engine.h"

/**
	Konstruktor & Destruktor
*/
Coin::Coin(double x, double y) : Entity(x, y) {
	initSprite();
}
Coin::~Coin(void){}


/**
	Metody publiczne
*/
void Coin::update(Map &map){

	_offset = map.getOffsetToEntity();

	_coin.update();
	
}

void Coin::draw() {
	_coin.drawCurrentFrame(getXOnScreen(), _y);
}

void Coin::initSprite(){
	try{
		_coin.setPattern(Engine::get().spriteDatabase()->get("coin"));
	}
	catch (exception &ex){
		al_show_native_message_box(al_get_current_display(),
								   "Error", "Blad 102",
								    ex.what(), NULL,
								    ALLEGRO_MESSAGEBOX_ERROR);
		exit(102);
	}
}