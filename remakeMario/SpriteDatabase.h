#ifndef SPRITEDATABASE_H
#define SPRITEDATABASE_H

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_native_dialog.h>

#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <exception>
#include <memory>	 // shared_ptr

#include "GameObject.h"


using namespace std;
//==============================================
// SpriteConfigPattern
//==============================================
/* wzorzec dotycz¹cy podstawowych w³asnoœci obiektu Sprite */
struct SpriteConfigPattern {

	int _maxFrame;				// liczba klatek w animacji
	int _curFrame;			   // aktualna klatka
	int _direction;			  // czy nastepna klakta jest na prawo czy lewo 
	int _posX;				 // pozycja x pierwszej klatki w atlasie
	int _posY;				// pozycja y pierwszej klatki w atlasie
	int _frameCount;	   // licznik klatek
	int _frameDelay;	  // opoznienie
	int _frameWidth;	 // szerokosc kaltki
	int _frameHeight;	// wysokosc klatki


	SpriteConfigPattern(int maxFrame, int curFrame, int dir, int frameCount, int frameDelay, int posX, int posY, int frameWidht, int frameHeight) :
		_maxFrame(maxFrame), _curFrame(curFrame), _direction(dir), _frameCount(frameCount), _frameDelay(frameDelay), _posX(posX), _posY(posY),
		_frameHeight(frameHeight), _frameWidth(frameWidht){};
	SpriteConfigPattern() :
		_maxFrame(0), _curFrame(0), _direction(0), _frameCount(0), _frameDelay(0), _posX(0), _posY(0), _frameHeight(0), _frameWidth(0){};
};



//==============================================
// SpriteDatabase
//==============================================
/* klasa wyj¹tków */
class configNotFound : public exception {
	string _exceptionName;
public:
	configNotFound(string name) : _exceptionName("Config not found: " + name) {};
	virtual const char* what() const throw() {
		return _exceptionName.c_str();
	}
};

class imageNotFound : public exception {
	string _exceptionName;
public:
	imageNotFound(string name) : _exceptionName("Image not found: " + name) {};
	virtual const char* what() const throw() {
		return _exceptionName.c_str();
	}
};

class SpriteDatabase {

	map<std::string, SpriteConfigPattern> _database;			 // mapa która przechowuje wszystkie zdefiniowane dostêpy do poszczególnych animacji spritów
	ALLEGRO_BITMAP *_atlas;								        // bitmapa na której znajduj¹ siê wszystkie dostêpne sprity
	ALLEGRO_BITMAP *_bg;									   // bitmapa przedstawiaj¹ca najdalsze t³o tj. same chmury
	ALLEGRO_BITMAP *_fg;									  // bitmapa przedstawiaj¹ca najbli¿sze krajobraz tj. krzaki itp.  


	/* Metody prywante:
    	Insert() - dodawanie specyfikacji dostêpu do spritów do bazy danych, wywo³ujemy tylko w konstruktorze by by³o
				   przejrzyœcie i aby odrazu wiedzieæ co mamy zdefiniowane w bazie.
	*/
	void Insert(const string& name, const SpriteConfigPattern& data);
public:

	SpriteDatabase();
	~SpriteDatabase();

	/* Gettery */
	SpriteConfigPattern & get(string name);
	ALLEGRO_BITMAP * getAtlas()  { return _atlas; };
	ALLEGRO_BITMAP * getBG()  { return _bg; };		
	ALLEGRO_BITMAP * getFG()  { return _fg; };	
};


typedef std::shared_ptr < SpriteDatabase > SpriteDatabasePtr;


#endif