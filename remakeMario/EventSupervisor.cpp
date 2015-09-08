#include "EventSupervisor.h"

/**
	konstruktor & destruktor
*/
EventSupervisor::EventSupervisor(size_t fps): _fps(fps), _timer(NULL), _eventQueue(NULL){
	/* Inicjalizacja mapy klawiszy */
	for (int i = 0; i < KEYSCNT; ++i)
		keys[i] = false;

	 cursorVector[0][0] = 0;
     cursorVector[0][1] = 0;

	/* Instalacja dodatków */
	al_install_keyboard();
	al_install_mouse();

	/* tworzenie timera oraz kolejki zdarzeñ */
	_eventQueue = al_create_event_queue();
	_timer = al_create_timer(1.0 / _fps);

	/* Przypisanie Ÿróde³ zdarzeñ */
	al_register_event_source(_eventQueue, al_get_timer_event_source(_timer));
	al_register_event_source(_eventQueue, al_get_keyboard_event_source());
	al_register_event_source(_eventQueue, al_get_mouse_event_source());
	al_register_event_source(_eventQueue, al_get_display_event_source(al_get_current_display()));

	al_start_timer(_timer);
}

EventSupervisor::~EventSupervisor(){
	al_destroy_timer(_timer);
	al_destroy_event_queue(_eventQueue);
}


/**
	Metody chronione
*/
void EventSupervisor::processEvents(ALLEGRO_EVENT &ev){

	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ) {
		cursorVector[1][0] = ev.mouse.x;
		cursorVector[1][1] = ev.mouse.y;
	}

	if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
		cursorVector[0][0] = ev.mouse.x;
		cursorVector[0][1] = ev.mouse.y;



	}

	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		keys[CLOSE] = true;
	}
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_ESCAPE:
			keys[ESC] = true;
			break;
		case ALLEGRO_KEY_LEFT:
			keys[LEFT] = true;
			break;
		case ALLEGRO_KEY_RIGHT:
			keys[RIGHT] = true;
			break;
		case ALLEGRO_KEY_UP:
			keys[UP] = true;
			break;
		case ALLEGRO_KEY_DOWN:
			keys[DOWN] = true;
			break;
		case ALLEGRO_KEY_SPACE:
			keys[SPACE] = true;
			break;
		case ALLEGRO_KEY_R:
			keys[KEY_R] = true;
			break;
		case ALLEGRO_KEY_Z:
			keys[KEY_Z] = true;
			break;
		case ALLEGRO_KEY_X:
			keys[KEY_X] = true;
			break;
		}
	} 
	else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_ESCAPE:
			keys[ESC] = false;
			break;
		case ALLEGRO_KEY_LEFT:
			keys[LEFT] = false;
			break;
		case ALLEGRO_KEY_RIGHT:
			keys[RIGHT] = false;
			break;
		case ALLEGRO_KEY_UP:
			keys[UP] = false;
			break;
		case ALLEGRO_KEY_DOWN:
			keys[DOWN] = false;
			break;
		case ALLEGRO_KEY_SPACE:
			keys[SPACE] = false;
			break;
		case ALLEGRO_KEY_R:
			keys[KEY_R] = false;
			break;
		case ALLEGRO_KEY_Z:
			keys[KEY_Z] = false;
			break;
		case ALLEGRO_KEY_X:
			keys[KEY_X] = false;
			break;
		}
	}
}