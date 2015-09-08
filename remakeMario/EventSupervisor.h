#ifndef EVENTSUPERVISOR_H
#define EVENTSUPERVISOR_H

#include <allegro5\allegro.h>

namespace keyid{
	enum KEYS{	UP,	DOWN, LEFT, RIGHT, SPACE, ESC, CLOSE, KEY_Z, KEY_X, KEY_R, KEYSCNT	};
}

using namespace keyid;

/** 
	Obiekty tej klasy s� nadzorcamy zdarze� - klawiatura + myszka.
	Modyfikuj� tablic� wykrywania zdarze� z danym przyciskiem / pozycj� myszki
*/
class EventSupervisor {
protected:

	ALLEGRO_EVENT_QUEUE *_eventQueue;	// kolejka zdarze�
	ALLEGRO_TIMER *_timer;			   // timer

	size_t _fps;					 // liczba klatek na sekunde

	bool keys[keyid::KEYSCNT];	   // tablica przechowuj�ca czy dany przycisk zosta� naci�ni�ty 
	int cursorVector[2][2];		  // tablica przechowuj�ca pozycje myszki gdy przycisk jest zwolniony oraz gdy jest naci�ni�ty

	/* Metoda obs�uj�ca zdarzenia */
	void processEvents(ALLEGRO_EVENT &ev);

public:
	EventSupervisor(size_t fps);
	virtual ~EventSupervisor();
};

#endif