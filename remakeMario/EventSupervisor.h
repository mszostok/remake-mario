#ifndef EVENTSUPERVISOR_H
#define EVENTSUPERVISOR_H

#include <allegro5\allegro.h>

namespace keyid{
	enum KEYS{	UP,	DOWN, LEFT, RIGHT, SPACE, ESC, CLOSE, KEY_Z, KEY_X, KEY_R, KEYSCNT	};
}

using namespace keyid;

/** 
	Obiekty tej klasy s¹ nadzorcamy zdarzeñ - klawiatura + myszka.
	Modyfikuj¹ tablicê wykrywania zdarzeñ z danym przyciskiem / pozycj¹ myszki
*/
class EventSupervisor {
protected:

	ALLEGRO_EVENT_QUEUE *_eventQueue;	// kolejka zdarzeñ
	ALLEGRO_TIMER *_timer;			   // timer

	size_t _fps;					 // liczba klatek na sekunde

	bool keys[keyid::KEYSCNT];	   // tablica przechowuj¹ca czy dany przycisk zosta³ naciœniêty 
	int cursorVector[2][2];		  // tablica przechowuj¹ca pozycje myszki gdy przycisk jest zwolniony oraz gdy jest naciœniêty

	/* Metoda obs³uj¹ca zdarzenia */
	void processEvents(ALLEGRO_EVENT &ev);

public:
	EventSupervisor(size_t fps);
	virtual ~EventSupervisor();
};

#endif