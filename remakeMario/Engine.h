#ifndef ENGINE_H
#define ENGINE_H

#include "SpriteDatabase.h"
#include "EntityFactory.h"
#include "TextManager.h"

enum GameState { HELLO, PAUSE, PLAYING, WIN, GAMEOVER, RESETGAME, CLOSEAPP, MENU };

class Engine {

	SpriteDatabasePtr _ptrSpriteDatabase;
	EntityFactoryPtr _ptrEntityFactory;
	TextManagerPtr  _ptrTextManager;
public:
	static Engine& get(){
		static Engine engine;
		return engine;	
	};

	/* Inicjalizacja*/
	void Load(){
		try{
			_ptrSpriteDatabase.reset( new SpriteDatabase() );
			_ptrEntityFactory.reset( new EntityFactory() );
			_ptrTextManager.reset( new TextManager() );
		}
		catch(fontNotFound &ex) {
			al_show_native_message_box(al_get_current_display(),
										"Error", "Error 103",
										ex.what(), NULL,
										ALLEGRO_MESSAGEBOX_ERROR);
			exit(103);
		}
		catch (exception &ex){
			al_show_native_message_box(al_get_current_display(),
										"Error", "Error 103",
										ex.what(), NULL,
										ALLEGRO_MESSAGEBOX_ERROR);
			exit(102);
		}
	};

	/* Gettery */
	SpriteDatabasePtr spriteDatabase() const {
		return _ptrSpriteDatabase;
	};
	EntityFactoryPtr entityFactory() const {
		return _ptrEntityFactory;
	};

	TextManagerPtr textManager() const {
		return _ptrTextManager;
	}
};

#endif