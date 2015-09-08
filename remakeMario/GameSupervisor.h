#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <vector>
#include <map>
#include <memory>

#include <allegro5\allegro.h>


#include "EventSupervisor.h"
#include "Player.h"
#include "Sprite.h"
#include "Map.h"
#include "Background.h"
#include "GoombaEntity.h"
#include "Flag.h"
#include "Engine.h"
#include "Menu.h"
#include "AlStarter.h"

using namespace std;



/*	Na podstawie tej klasy mo�na stworzy� obiekt kt�ry zarz�dza przebiegiem gry. */
class GameSupervisor:  public AlStarter, public EventSupervisor {

	/* Aliasy */
	typedef map< string, vector< GameObjectPtr > >::iterator _iterBuff;
	typedef map< string, vector< GameObjectPtr > >::reverse_iterator _reverseIterBuff;
	typedef vector< GameObjectPtr >::iterator _iterGameObj;

	map<string, vector< GameObjectPtr > > _depthBuffer;	//Kolekcja wszystkich aktualnie utworzonych obiekt�w.

	MapPtr _mapView;				// obiekt klasy reprezentuj�cej logik� mapy przewijanej
	BackgroundPtr background;	   // obiekt klasy reprezentuj�cy logik� t�a z zastosowanie zjawiska paralaksy
	FlagPtr _ptrFlag;			  // Wska�nik na obiekt flagi, potrzebny do jej osobnej aktualizacji podczas zaliczonego poziomu
	Menu menu;					 // obiekt reprezentuj�cy menu gry

	PlayerPtr mario;			// obiekt klasy reprezentuj�cej gracza

	bool _isDone;			  // flaga oznaczaj�ca koniec p�tli g��wnej gry
	bool _redraw;			 // flaga oznaczaj�ca czy nalezy wykona� ponowne wyrysowanie wszystkich obiekt�w

	GameState _state;	   // akutalny stan gry

	size_t _lvlNumber;	 // aktualny nr poziomu

	/* Metody prywatne */
	// akutalizacja logiki gry, jako argument wywo�ania podajemy aktualny obiekt reprezentuj�cy zaistnia�e zdarzenie
	void gameUpdate(ALLEGRO_EVENT &ev);	
	void render();						// metoda zajmuje si� wyrysowywaniem obiekt�w
	void sleepAndAddEnities();		   // dodawanie oraz usypianie jednostek
	void eraseDeadEntites();		  // usuwanie nie�ywych jednostek
	void initGame();


	void checkPlayerEntitiesCollisions(); // sprawdzanie kolizji gracza z innymi jednostkami

	void playingUPDATE();	// akutalizacja zwi�zana z logik� podczas aktywnej gry
public:
	GameSupervisor(size_t width, size_t height, int flag = 0);
	~GameSupervisor();

	/**
		Metody publiczne:
		gameLoop() - g�owna p�tla gry, wykonywane zostanie sprawdzenie czy nast�pi�o jakie� zdarzenie, akutualizacja logiki oraz render je�li zajdzie potrzeba
					 Wszystko dzieje si� ze sta�a r�wn� EventSupervisor::_fps
	*/
	void gameLoop();
};


#endif