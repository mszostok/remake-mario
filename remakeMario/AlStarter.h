#ifndef ALSTARTER_H
#define ALSTARTER_H

#pragma warning(disable: 4290)

#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_image.h>

#include <exception>

using namespace std;


/*	Na podstawie tej klasy mo�na stworzy� obiekt reprezentuj�cy okno aplikacji.  */
class AlStarter{

	/* Klasy wyj�tk�w */
	class alInitException : public exception {
		virtual const char* what() const throw() {
			return "Failed to initialize Allegro.";
		}
	};
	class displayException : public exception{
		virtual const char* what() const throw() {
			return "Failed to set up display.";
		}
	};

	/*Metody prywatne */

	//incjalizajca okna, w razie niepowodzenia zostan� rzucone odpowiednie wyj�tki
	void init() throw(alInitException, displayException);

protected:

	size_t _displayWidth,		     //szeroko�� okna
		   _displayHeight;		    // wysoko�� okna
	int    _fullscreen;            // 1 - fullscreen, 0 - normalne okno aplikacji
	ALLEGRO_DISPLAY *_display;    //uchwyt okna
	ALLEGRO_BITMAP  *_icon;      // bitmapa przechowujaca ikon� aplikacji

public:

	AlStarter(size_t width, size_t height, int flag = NULL);
	virtual ~AlStarter();
};

#endif