#ifndef MENU_H
#define MENU_H

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_native_dialog.h>

#include "Sprite.h"
#include "Engine.h"
#include "Aabb.h"

enum btnType { EXIT, RESET, PLAY, BTNCNT};
enum btnState { ON, OFF };
enum cursorVectorEvent { NOACTION, BTNUP };
enum cursorVectorAxis { X, Y };

class Menu {
	size_t _windowsWidth;				// szerokoœæ okna aplikacji
	size_t _windowsHeigth;			   // wysokoœæ okna aplikacji

	Sprite _btnExit[2];				 // tablica przechowuj¹ca sprite ( wygl¹d przycisku) dla dwóch stanów - normalny oraz po najechaniu myszk¹
	Sprite _btnPlay[2];				// tablica przechowuj¹ca sprite ( wygl¹d przycisku) dla dwóch stanów - normalny oraz po najechaniu myszk¹
	Sprite _btnReset[2];		   // tablica przechowuj¹ca sprite ( wygl¹d przycisku) dla dwóch stanów - normalny oraz po najechaniu myszk¹

	bool _btnCollide[BTNCNT];	 // tablica przechowuj¹ca czy nast¹pi³a kolizja z danym przyciskiem 

	/* AABB otaczaj¹ce przyciski */
	Aabb getAabbReset() const {
		Aabb box(50 + 10, _windowsHeigth/2 - 70 + 10, 50,  70 - 45);
        return box;
    };
	Aabb getAabbExit() const {
		Aabb box(55, _windowsHeigth/2 + 10, 50, 35);
        return box;
    };
	Aabb getAabbPlay() const {
		Aabb box(150 - 30 + 15, _windowsHeigth/2 - 35 +15, 30,  30);
        return box;
    };

public:
	Menu();
	virtual ~Menu();

	/* Modyfikatory */
	void initSprites();
	void draw();
	void update(int vector[][2], GameState &state);
};

#endif