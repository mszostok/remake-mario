#include "Map.h"


#include "Engine.h"

//==============================================
// Map
//==============================================

/**
	konstruktor & destruktor
*/

Map::Map(string lvl) : _visibleWidth(al_get_display_width(al_get_current_display()) / mapSpace::tileWidth), _height(al_get_display_height(al_get_current_display()) / mapSpace::tileHeight){
	
	_width = _visibleWidth + 2; // dodatkowe pola

	_actualLvl.loadFromFile(lvl);

	initTilesDatabase();


	/* Debug, dla release usun¹æ */
	al_init_font_addon();
	al_init_ttf_addon();

	font18 = al_load_font("arial.ttf", 18, 0);
	////////////////////////////////////////////////
};

Map::~Map(){
	al_destroy_font(font18);
};

/**
	Metody prywatne
*/

void Map::initTilesDatabase(){

	_spritesTilesDatabase.resize(mapSpace::CNT);

	storeSprite(pipeRightBottom, "pipeRightBottom");
	storeSprite(pipeLeftBottom, "pipeLeftBottom");
	storeSprite(pipeRightTop, "pipeRightTop");
	storeSprite(pipeLeftTop, "pipeLeftTop");
	storeSprite(blockRightEnd, "rightEnd");
	storeSprite(blockLeftEnd, "leftEnd");
	storeSprite(ground, "ground");
	storeSprite(brick, "brick");
	storeSprite(block, "block");
}

void Map::storeSprite(TilesType tt, string name){

		_spritesTilesDatabase[tt] = Sprite(Engine::get().spriteDatabase()->get(name));

}

/**
	Metody publiczne
*/


void Map::update(int max_x_position_mulBy45, double offset){

	int halfVisibleAreaWidth = _visibleWidth/2;
	_offset = offset;

	_leftStartX	= (max_x_position_mulBy45 / tileWidth) - halfVisibleAreaWidth;

	if (_leftStartX < 0)
		_leftStartX = 0;
	
	if (static_cast<size_t>(max_x_position_mulBy45) < halfVisibleAreaWidth*tileWidth)	// lewa strona platformy
		_draw = leftEnd;

	 // ?rodek platformy (dopóki szeroko?? obszaru kt b?dzie za?adowany do pami?ci + pocz?tek od którego nale?y
	// zacz?? wczytywanie z mapy poziomy nie przekraczaj? d?ugo?? poziomu)
	else if (static_cast<size_t>(_width + _leftStartX) <= _actualLvl.getWidth())     
		_draw = midPart;

	else												      // prawa strona platformy
		_draw = rightEnd;

}

void Map::draw(){

	switch (_draw)	{
	case midPart: drawPlatformMidPart();
		break;
	case rightEnd: drawPlatformRightEnd();
		break;
	case leftEnd: drawPlatformLeftEnd();
		break;
	default:
		break;
	}

}

void Map::drawPlatformLeftEnd(){

	for (size_t y = 0; y < _height; ++y) {
		for (size_t x = _leftStartX; x <_width + _leftStartX; ++x) {
			const TilesType& ft = _actualLvl.field(x, y);

			if (ft != TilesType::none) {
				_spritesTilesDatabase[ft].drawCurrentFrame(x*tileWidth + _offset, y*tileHeight);
			}
		}
	}
};

void Map::drawPlatformMidPart(){
	for (size_t y = 0; y < _height; ++y) {
		for (size_t draw_x = 0, x = _leftStartX; x < _width + _leftStartX; ++draw_x, ++x) {
			const TilesType& ft = _actualLvl.field(x, y);

			if (ft != TilesType::none) {
				_spritesTilesDatabase[ft].drawCurrentFrame(static_cast<int>(draw_x) * 45 - 45 + _offset, y*tileHeight);
			}
		}
	}
};

void Map::drawPlatformRightEnd(){

	int leftStart = _actualLvl.getWidth() - _visibleWidth;

	for (size_t y = 0; y < _height; ++y) {
		for (size_t draw_x = 0, x = leftStart; x < _actualLvl.getWidth(); ++x, ++draw_x) {

			const TilesType& ft = _actualLvl.field(x, y);
			al_draw_textf(font18, al_map_rgb(255, 0, 255), 100, 100, 0, "tu jestesm");

			if (ft != TilesType::none) {
				_spritesTilesDatabase[ft].drawCurrentFrame(draw_x * tileWidth, y*tileHeight);
			}
		}
	}
};