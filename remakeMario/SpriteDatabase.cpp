#include "SpriteDatabase.h"

//==============================================
// SpriteDatabase
//==============================================
/**
	Konstruktor & destruktor
*/
SpriteDatabase::SpriteDatabase(){
	al_init_image_addon();

    _atlas = al_load_bitmap("data/atlas.png");
	_bg = al_load_bitmap("data/bg.bmp");
	_fg = al_load_bitmap("data/fg.png");

	if( !_atlas )
		throw imageNotFound("atlas.png");
	if( !_bg )
		throw imageNotFound("bg.png");	
	if( !_fg )
		throw imageNotFound("fg.png");

	al_convert_mask_to_alpha(_atlas, al_map_rgb(0, 255, 0));
	//int maxFrame, int curFrame, int dir, int frameCount, int frameDelay, int posX, int posY, int frameWidht, int frameHeight
	Insert("marioLeft", SpriteConfigPattern(3, 0, -1, 0, 8, 3 * 45, 0 * 35, 45, 35));
	Insert("marioRight", SpriteConfigPattern(3, 0, 1, 0, 8, 4 * 45, 0 * 35, 45, 35));

	Insert("UPGRADEmarioLeft", SpriteConfigPattern(3, 0, -1, 0, 8, 3 * 45, 1 * 35, 45, 70));
	Insert("UPGRADEmarioRight", SpriteConfigPattern(3, 0, 1, 0, 8, 4 * 45, 1 * 35, 45, 70));

	Insert("goombaLeft", SpriteConfigPattern(3, 0, -1, 0, 10, 3 * 45, 3 * 35, 45, 35));
	Insert("goombaRight", SpriteConfigPattern(3, 0, 1, 0, 10, 4 * 45, 3 * 35, 45, 35));

	Insert("ground", SpriteConfigPattern(0, 0, 0, 0, 0, 0 * 45, 4 * 35, 45, 35));
	Insert("block", SpriteConfigPattern(0, 0, 0, 0, 0, 1 * 45, 4 * 35, 45, 35));
	Insert("rightEnd", SpriteConfigPattern(0, 0, 0, 0, 0, 2 * 45, 4 * 35, 45, 35));	
	Insert("leftEnd", SpriteConfigPattern(0, 0, 0, 0, 0, 3 * 45, 4 * 35, 45, 35));
	Insert("pipeLeftBottom", SpriteConfigPattern(0, 0, 0, 0, 0, 4 * 45, 4 * 35, 45, 35));
	Insert("pipeRightBottom", SpriteConfigPattern(0, 0, 0, 0, 0, 5 * 45, 4 * 35, 45, 35));
	Insert("pipeLeftTop", SpriteConfigPattern(0, 0, 0, 0, 0, 6 * 45, 4 * 35, 45, 35));
	Insert("pipeRightTop", SpriteConfigPattern(0, 0, 0, 0, 0, 7 * 45, 4 * 35, 45, 35));
	Insert("brick", SpriteConfigPattern(0, 0, 0, 0, 0, 0 * 45, 5 * 35, 45, 35));

	Insert("coin", SpriteConfigPattern(6, 0, 1, 0, 8, 0, 6 * 35, 45, 35));

	Insert("btnResetON", SpriteConfigPattern(0, 0, 0, 0, 0, 0 * 60, 7 * 35, 60, 60));
	Insert("btnExitON", SpriteConfigPattern(0, 0, 0, 0, 0, 1 * 60, 7 * 35, 60, 60));
	Insert("btnPlayON", SpriteConfigPattern(0, 0, 0, 0, 0, 2 * 60, 7 * 35, 60, 60));
	Insert("btnResetOFF", SpriteConfigPattern(0, 0, 0, 0, 0, 3 * 60, 7 * 35, 60, 60));
	Insert("btnExitOFF", SpriteConfigPattern(0, 0, 0, 0, 0, 4 * 60, 7 * 35, 60, 60));
	Insert("btnPlayOFF", SpriteConfigPattern(0, 0, 0, 0, 0, 5 * 60, 7 * 35, 60, 60));

	Insert("pipeFlag", SpriteConfigPattern(0, 0, 0, 0, 0, 8 * 45, 0, 45, 8*35));
}


SpriteDatabase::~SpriteDatabase(){
	al_destroy_bitmap(_atlas);
	al_destroy_bitmap(_bg);
	al_destroy_bitmap(_fg);
}


/**
	Metody prywatne
*/

void SpriteDatabase::Insert(const string& name, const SpriteConfigPattern& data) {
	_database.insert(std::make_pair(name, data));

}

/**
	Metody publiczne
*/

SpriteConfigPattern  &SpriteDatabase::get(string name)  {

	auto search = _database.find(name);
	if (search != _database.end()) {
		return (search->second);
	}
	else {
		throw configNotFound(name);
	}
}
