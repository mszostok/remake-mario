#ifndef MAP_H
#define MAP_H

#include <vector>
#include <memory>

#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h> // wyświetlanie wyjątku

#include <allegro5\allegro_font.h>	// dla debug, w release wyrzucić
#include <allegro5\allegro_ttf.h>  // -..-

#include "Sprite.h"
#include "Level.h"


using namespace mapSpace;
using namespace std;


enum DrawInfo{ midPart, rightEnd, leftEnd};



//==============================================
// Map
//==============================================
/* obiekt tej klasy reprezentuje mapę gry, realizuję logikę mapy scrollowanej */
class Map : public GameObject {

	ALLEGRO_FONT * font18;					 //debug, dla release usunąć
	
	vector<Sprite> _spritesTilesDatabase;  //_sprites[t] jest sprite reprezentujący typ pola t. (ad. jeśli zmienimy na strukture kafelek kt 
										  // bd zawierała m.in. sprite to zmiana nazwy na samo tilesDatabase)

	Level _actualLvl;					// akutalnie wczytana mapa poziomu gry

	size_t _width;					  // szerokość wyświetlanej mapy powiększona o 2 jednostki (jedna niewidoczna z prawej i jedna z lewej,
									 // potrzebne przy przewijaniu mapy)
	size_t _visibleWidth;			// szerokość wyświetlanej mapy
	size_t _height;				   // wysokość (taka sama dla obu powyższych przypadków, ponieważ nie ma możliwości przewijania mapy w pionie

	int _leftStartX;			 // wartość osi OX od której należy zacząć ładowanie poziomu do pamięci  
	double _offset;				// offset o który ma się przesunąć cała mapa (scrollowanie mapy)

	DrawInfo _draw;			  // akutalny stan mapy. Informacja o tym którą część należy wyświetlić (lewą stronę, środek lub prawą stronę)



	void storeSprite(TilesType tt, string name);	// zapamiętywanie spritów
	void initTilesDatabase();					   // metoda inicjalizująca bazę dostępnych rodzajów kafelek na mapie

public:
	Map(string lvl);
	~Map();

	/* rysowanie mapy aktualnej mapy na ekranie w zale¿noœci od dx( przesunięcia) */
	void draw();

	void drawPlatformLeftEnd();
	void drawPlatformMidPart();
	void drawPlatformRightEnd();
	
	/* Gettery */
	Level & getLevel() { return _actualLvl; };
	size_t getLevelWidth() const { return _actualLvl.getWidth(); };

	double getOffsetToEntity() { 
		if(_draw == midPart)
			return (_leftStartX +1) * tileWidth +  (-_offset);
		else 
			return -_offset;
	};

	/* Modfikatory */
	void update(int max_x_position_mulBy45, double offset);
};


typedef std::shared_ptr < Map> MapPtr;



#endif