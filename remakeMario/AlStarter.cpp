#include "AlStarter.h"

/**
	Konstruktor & Destruktor
*/
AlStarter::AlStarter(size_t width, size_t height, int flag) : _displayWidth(width), _displayHeight(height), _fullscreen(flag), _display(NULL), _icon(NULL){

	try{
		init();
	}
	catch (exception &ex){
		al_show_native_message_box(NULL,
								   "Error", "Blad 101",
								   ex.what(),
								   NULL, 
								   ALLEGRO_MESSAGEBOX_ERROR);
		exit(101);
	}


};

AlStarter::~AlStarter(){
	al_destroy_bitmap(_icon);
	al_destroy_display(_display);
}


/** 
	Metody prywatne
*/

void AlStarter::init(){

	/* Inicjalizacja */
	if (!al_init())														    //inicjalizacja Allegro
		throw alInitException();

	al_set_new_display_flags(ALLEGRO_NOFRAME);
	_display = al_create_display(_displayWidth, _displayHeight);		//tworzenie obiektu display

	if (!_display)													  //test obiektu
		throw displayException();


	/* Instalacja dodatków */
	al_init_image_addon();



	/* Ustawienie ikony */
	_icon = al_load_bitmap("data/ic.bmp");

	if( !_icon )
		throw alInitException();

	al_convert_mask_to_alpha(_icon, al_map_rgb(0, 0, 0));
	al_set_display_icon(_display, _icon);
}