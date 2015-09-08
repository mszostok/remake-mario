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



/*	Na podstawie tej klasy mo¿na stworzyæ obiekt który zarz¹dza przebiegiem gry. */
class GameSupervisor:  public AlStarter, public EventSupervisor {

	/* Aliasy */
	typedef map< string, vector< GameObjectPtr > >::iterator _iterBuff;
	typedef map< string, vector< GameObjectPtr > >::reverse_iterator _reverseIterBuff;
	typedef vector< GameObjectPtr >::iterator _iterGameObj;

	map<string, vector< GameObjectPtr > > _depthBuffer;	//Kolekcja wszystkich aktualnie utworzonych obiektów.

	MapPtr _mapView;				// obiekt klasy reprezentuj¹cej logikê mapy przewijanej
	BackgroundPtr background;	   // obiekt klasy reprezentuj¹cy logikê t³a z zastosowanie zjawiska paralaksy
	FlagPtr _ptrFlag;			  // WskaŸnik na obiekt flagi, potrzebny do jej osobnej aktualizacji podczas zaliczonego poziomu
	Menu menu;					 // obiekt reprezentuj¹cy menu gry

	PlayerPtr mario;			// obiekt klasy reprezentuj¹cej gracza

	bool _isDone;			  // flaga oznaczaj¹ca koniec pêtli g³ównej gry
	bool _redraw;			 // flaga oznaczaj¹ca czy nalezy wykonaæ ponowne wyrysowanie wszystkich obiektów

	GameState _state;	   // akutalny stan gry

	size_t _lvlNumber;	 // aktualny nr poziomu

	/* Metody prywatne */
	// akutalizacja logiki gry, jako argument wywo³ania podajemy aktualny obiekt reprezentuj¹cy zaistnia³e zdarzenie
	void gameUpdate(ALLEGRO_EVENT &ev);	
	void render();						// metoda zajmuje siê wyrysowywaniem obiektów
	void sleepAndAddEnities();		   // dodawanie oraz usypianie jednostek
	void eraseDeadEntites();		  // usuwanie nie¿ywych jednostek
	void initGame();


	void checkPlayerEntitiesCollisions(); // sprawdzanie kolizji gracza z innymi jednostkami

	void playingUPDATE();	// akutalizacja zwi¹zana z logik¹ podczas aktywnej gry
public:
	GameSupervisor(size_t width, size_t height, int flag = 0);
	~GameSupervisor();

	/**
		Metody publiczne:
		gameLoop() - g³owna pêtla gry, wykonywane zostanie sprawdzenie czy nast¹pi³o jakieœ zdarzenie, akutualizacja logiki oraz render jeœli zajdzie potrzeba
					 Wszystko dzieje siê ze sta³a równ¹ EventSupervisor::_fps
	*/
	void gameLoop();
};


#endif