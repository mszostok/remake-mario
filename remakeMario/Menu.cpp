#include "Menu.h"

/**
	Konstruktor & Destruktor
*/
Menu::Menu(){
	for(int i = 0; i < BTNCNT; ++i)
		_btnCollide[i] = false;

	al_init_primitives_addon();

	_windowsWidth = al_get_display_width(al_get_current_display());
	_windowsHeigth = al_get_display_height(al_get_current_display());
}
Menu::~Menu(){}



/**
	Metody publiczne
*/
void Menu::draw() {
	/* Zaciemnienie t³a  oraz lewy prostok¹t*/
	al_draw_filled_rectangle(0, 0, _windowsWidth, _windowsHeigth, al_map_rgba( 0, 0, 0, 215 ));
	al_draw_filled_rectangle(0, 0, 150, _windowsHeigth, al_map_rgb( 41, 134, 113));

	/* Separator */
	al_draw_filled_rectangle(150, 0, 152, _windowsHeigth, al_map_rgb( 255, 189, 49));
	al_draw_filled_rectangle(152, 0, 153, _windowsHeigth, al_map_rgb( 239, 237, 199));
	al_draw_filled_rectangle(153, 0, 155, _windowsHeigth, al_map_rgb( 255, 189, 49));

	/* Przyciski */
	_btnReset[!_btnCollide[RESET]].drawCurrentFrame(50, _windowsHeigth/2 - 70);
	_btnExit[!_btnCollide[EXIT] ].drawCurrentFrame(50, _windowsHeigth/2);
	_btnPlay[!_btnCollide[PLAY] ].drawCurrentFrame(150 - 30, _windowsHeigth/2 - 35);

}


/**
	Modyfikatory
*/
void Menu::initSprites(){
	try{
		_btnExit[OFF].setPattern(Engine::get().spriteDatabase()->get("btnExitOFF"));
		_btnExit[ON].setPattern(Engine::get().spriteDatabase()->get("btnExitON"));
		_btnReset[OFF].setPattern(Engine::get().spriteDatabase()->get("btnResetOFF"));
		_btnReset[ON].setPattern(Engine::get().spriteDatabase()->get("btnResetON"));
		_btnPlay[OFF].setPattern(Engine::get().spriteDatabase()->get("btnPlayOFF"));
		_btnPlay[ON].setPattern(Engine::get().spriteDatabase()->get("btnPlayON"));

	}
	catch (exception &ex){
		al_show_native_message_box(al_get_current_display(),
								   "Error", "Blad 105",
								    ex.what(), NULL,
								    ALLEGRO_MESSAGEBOX_ERROR);
		exit(102);
	}
}

void Menu::update(int vector[][2], GameState &state) {
	/* reset stanu przycisków */
	for(int i = 0; i < BTNCNT; ++i)
		_btnCollide[i] = false;

	/* Aktualizacja stanów przycisków dla myszki która na nie tylko najecha³a*/
	Aabb cBox(vector[NOACTION][X], vector[NOACTION][Y], 1, 1);

	if( getAabbReset().collides(cBox))
		_btnCollide[RESET] = true;

	if( getAabbExit().collides(cBox))
		_btnCollide[EXIT] = true;

	if( getAabbPlay().collides(cBox))
		_btnCollide[PLAY] = true;

	/* Zwrócenie stanu przycisków dla myszki która zosta³a naciœniêta i zwolniona */
	cBox.Move(vector[BTNUP][X], vector[BTNUP][Y]);

	if( getAabbReset().collides(cBox)) {
		vector[BTNUP][X] = -1; vector[BTNUP][Y] = -1;
		state = GameState::RESETGAME;
	}
	if( getAabbExit().collides(cBox)){
		vector[BTNUP][X] = -1; vector[BTNUP][Y] = -1;
		state = GameState::CLOSEAPP;
	}
	if( getAabbPlay().collides(cBox)) {
		vector[BTNUP][X] = -1; vector[BTNUP][Y] = -1;
		state = GameState::PLAYING;
	}
}