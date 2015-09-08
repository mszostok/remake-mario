#include "Flag.h"
#include "Engine.h"

/**
	Konstruktory & destruktor
*/
Flag::Flag(double x, double y) : Entity(x, y), _heightOffset(6*35 +2){

	initSprite();
	_y -= 7 * 35;
}
Flag::~Flag(void){}


/**
	Metody publiczne
*/
void Flag::update(Map &map){

	_offset = map.getOffsetToEntity();

	_flag.update();
}

bool Flag::setWin() {
	_flag.update();

	if( _heightOffset > 0 ){
		_heightOffset -= 5;
		return false;
	}

	return true;
}

void Flag::draw() {
	_pipe.drawCurrentFrame(getXOnScreen(), _y);
	_flag.drawCurrentFrame(getXOnScreen(), _y + _heightOffset);
}

void Flag::initSprite(){
	try{
		_pipe.setPattern(Engine::get().spriteDatabase()->get("pipeFlag"));
		_flag.setPattern(Engine::get().spriteDatabase()->get("coin"));
	}
	catch (exception &ex){
		al_show_native_message_box(al_get_current_display(),
								   "Error", "Blad 102",
								    ex.what(), NULL,
								    ALLEGRO_MESSAGEBOX_ERROR);
		exit(102);
	}
}