#include "TextManager.h"


/**
	Konstruktor & Destruktor
*/
TextManager::TextManager(void){

	/* inicjalizacja modu³u czcionek */
	al_init_font_addon();
	al_init_ttf_addon();

	font13 = al_load_font("data/fonts/arial.ttf", 13, 0);
	fontMario20 = al_load_font("data/fonts/SuperMarioBros.ttf", 25, 0);

	/* wyrzucenie wyj¹tku, jeœli któraœ z czcionek nie zosta³a poprawnie wczytana */
	if( !font13 )
		throw fontNotFound("arial.ttf");
	if( !fontMario20 )
		throw fontNotFound("SuperMarioBros.ttf");
 
}
TextManager::~TextManager(void){
	al_destroy_font(font13);
	al_destroy_font(fontMario20);
}


/**
	Metody publiczne
*/
void TextManager::drawText(int r, int g, int b, int x, int y, string text, int value) {

	al_draw_textf(fontMario20, al_map_rgb(r, g, b), x, y, 0, text.c_str(), value );
}

void TextManager::drawText(int x, int y, string text, int flag, int value) {

	al_draw_textf(fontMario20, al_map_rgb(255, 255, 255), x, y, flag, text.c_str(), value );

}

void TextManager::drawTextInfo(int x, int y, string text, int flag, int value) {

	al_draw_textf(font13, al_map_rgb(255, 255, 255), x, y, flag, text.c_str(), value );

}