#include "GameSupervisor.h"

using namespace keyid;
/**
	 konstruktor & destruktor
*/

GameSupervisor::GameSupervisor(size_t width, size_t height, int flag) 
	:  AlStarter(width, height, flag),  EventSupervisor(60), _redraw(false), _state(HELLO), _isDone(false), _ptrFlag(NULL),
	   _lvlNumber(1) {

	/* inicjalizacja silnika */
	Engine::get().Load();
	
	menu.initSprites();

	initGame();
}

GameSupervisor::~GameSupervisor(){}


/**
	Metody prywatne
*/
void GameSupervisor::initGame() {
	/* ustalenie poziomu */
	if( _lvlNumber > 2)
		_lvlNumber = 2;

	/* inicjalizjaca obiektów */
	try {
	_mapView.reset( new Map(std::to_string(_lvlNumber)));
    mario.reset( new Player(45, 100, _mapView->getLevelWidth()));
	background.reset( new Background());
	}
	catch (imageNotFound &ex){
		al_show_native_message_box(al_get_current_display(),
								   "Error", "Error 102",
								    ex.what(), NULL,
								    ALLEGRO_MESSAGEBOX_ERROR);
		exit(102);
	}
	catch (FileNotFound &ex){
		al_show_native_message_box(al_get_current_display(),
								   "Error", "Error 104",
									ex.what(), NULL,
									ALLEGRO_MESSAGEBOX_ERROR);
		exit(104);
	}
	catch (configNotFound &ex){
		al_show_native_message_box(al_get_current_display(),
								   "Error", "Error 105" ,
									ex.what(), NULL,
									ALLEGRO_MESSAGEBOX_ERROR);
		exit(105);
	}


	catch (exception &ex){
		al_show_native_message_box(al_get_current_display(),
								   "Error",ex.what(),
									NULL, NULL,
									ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}


	/* dodanie obiektów do _depthBuffer */ 
	vector< GameObjectPtr > fg;
	vector< GameObjectPtr > bg;

	bg.push_back(background);
	bg.push_back(_mapView);
	fg.push_back(mario);

	_depthBuffer.clear();
	_ptrFlag = NULL;

	_depthBuffer.insert(make_pair("BG", bg));
	_depthBuffer.insert(make_pair("FG", fg));
}

void GameSupervisor::playingUPDATE(){


	if (keys[UP] || keys[SPACE] || keys[KEY_Z])
		mario->jump();

	if (keys[KEY_R])
		mario->resetAnimation();

	mario->setXAcceleration( keys[KEY_X]);
	
	if (keys[LEFT])
		mario->moveLeft();
	else if (keys[RIGHT])
		mario->moveRight();
	else 
		mario->stay();

	/* usuniêcie martwych jednostek */
	eraseDeadEntites();

	/* Dodanie oraz uœpienie jednostek */
	sleepAndAddEnities();

	/* sprawdzanie wyst¹pienia kolizji: jednostka-jednostka, gracz-jednostka */
	checkPlayerEntitiesCollisions();

	/* aktualizacja logiki jednostek */
	for (_reverseIterBuff it1 = _depthBuffer.rbegin(); it1 != _depthBuffer.rend(); ++it1) {
		for (_iterGameObj it2 = it1->second.begin(); it2 != it1->second.end(); ++it2) {

			BackgroundPtr tmpBG =  std::dynamic_pointer_cast< Background > (*it2);
			EntityPtr tmpEntity = std::dynamic_pointer_cast< Entity >(*it2);
			MapPtr tmpMap = std::dynamic_pointer_cast< Map >(*it2);


			if (tmpEntity)
				tmpEntity->update(*_mapView);
			else if (tmpMap)
				tmpMap->update(mario->getAchievedXMulByTileWidth(), mario->getDeltaXToNextTileWidth());
			else if (tmpBG)
				tmpBG->update(mario->getVelX());
			else
				(*it2)->update();
		}
	}
}

void GameSupervisor::gameUpdate(ALLEGRO_EVENT &ev){

	if (ev.type == ALLEGRO_EVENT_TIMER)	{
		_redraw = true;

		// jeœli nacisniemy przycisk zamknij
		if(keys[CLOSE])		
			_isDone = true;

		// jeœli gracz nie posiada ju¿ ¿adnych ¿yæ to zmieñ stan na gameover
		if( mario->getLifes() <= 0 ) {
			_state = GAMEOVER;
		}

		// jeœli gracz osi¹gn¹c checkpoint na mapie to zmieñ stan na win
		if( mario->isWin()) {	
			_state = WIN;
		}

		// ekran powitalny
		if ( _state == HELLO )			
			menu.update(cursorVector, _state);

		// jeœli naciœniemy ESC to przechodzimy do ekranu pauzy tylko jeœli nie ma HELLO lub GAMEOVER
		if (keys[ESC] && _state != HELLO && _state != GAMEOVER && _state != WIN )	
			_state = PAUSE;

		// ekran pauzy
		if ( _state == PAUSE ) 
			menu.update(cursorVector, _state);
		
		// ekran gry przegranej
		if ( _state == GAMEOVER ) {
			menu.update(cursorVector, _state);
			if(_state == PLAYING )
				_state = RESETGAME;
		}
		// ekran wygranej
		if ( _state == WIN ) {
			menu.update(cursorVector, _state);
			if(_state == PLAYING ) {
				_state = RESETGAME;
				++_lvlNumber;
			}
			
		}
		// reset gry
		if ( _state ==  RESETGAME ) {
			initGame();
			_state = PLAYING;
		}

		// zamkniecie aplikacji za pomoc¹ menu
		if ( _state == CLOSEAPP){
			_isDone = true;
			_redraw = false;
		}
		// aktywan gra
		else if ( _state == PLAYING)
			playingUPDATE();
	}

}

void GameSupervisor::render(){

	if (_redraw && al_is_event_queue_empty(_eventQueue)){

		_redraw = false;


			/* rysowanie obiektów wed³ug z-buffer (bufor g³êbokoœci) */
			for (_iterBuff it1 = _depthBuffer.begin(); it1 != _depthBuffer.end(); ++it1){
				for (_iterGameObj it2 = it1->second.begin(); it2 != it1->second.end(); ++it2){
					(*it2)->draw();
				}
			}

			/* Wyœwietlanie informacji */
			Engine::get().textManager()->drawText(50, 30, "MARIO x  %i", 0,  mario->getLifes());
			Engine::get().textManager()->drawText(335, 30, "SCORE x  %i", 0, mario->getScore());
			Engine::get().textManager()->drawText(640, 30, "WORLD");
			Engine::get().textManager()->drawText(660, 55, "1-1");

		if ( _state == HELLO ) {
			background->update(0);
			menu.draw();
			Engine::get().textManager()->drawText(1100/2, 200/2, "R E M A K E   G R Y", ALLEGRO_ALIGN_CENTER);
			Engine::get().textManager()->drawText(1100/2, 200/2 + 35, "M A R I O", ALLEGRO_ALIGN_CENTER);
			
			Engine::get().textManager()->drawText(1100/2, 500/2 + 2*35, "Na strzalkach poruszamy sie w prawo i w lewo,", ALLEGRO_ALIGN_CENTER);
			Engine::get().textManager()->drawText(1100/2, 500/2 + 3*35, "oraz skaczemy.", ALLEGRO_ALIGN_CENTER);
			Engine::get().textManager()->drawTextInfo(990, 575, "Jest to wczesna wersja rozwojowa. Copyright by Mateusz Szostok", ALLEGRO_ALIGN_RIGHT);
		}
	
		if ( _state == PAUSE ) {
			background->update(0);
			menu.draw();
			Engine::get().textManager()->drawText(1100/2, 595/2, "PAUZA", ALLEGRO_ALIGN_CENTER);
		}

		if ( _state == GAMEOVER ) {
			background->update(0);
			menu.draw();
			Engine::get().textManager()->drawText(1100/2, 55, "SCORE x  %i",  ALLEGRO_ALIGN_CENTER, mario->getScore());
			Engine::get().textManager()->drawText(1100/2, 595/2, "PRZEGRANA", ALLEGRO_ALIGN_CENTER);
		}

		if ( _state == WIN ) {
			background->update(0);

			if( _ptrFlag->setWin() ) {
				menu.draw();
				Engine::get().textManager()->drawText(1100/2, 55, "SCORE x  %i",  ALLEGRO_ALIGN_CENTER, mario->getScore());
				Engine::get().textManager()->drawText(1100/2, 595/2, "POZIOM ZDOBYTY", ALLEGRO_ALIGN_CENTER);
			}
		}

		/* wyœwietlenie na ekran + czyszczenie bitmapy bufora kolorem zielonym*/
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 255, 0));
	}
}

void GameSupervisor::eraseDeadEntites(){

	list<LevelEntityData> & ents = _mapView->getLevel().getEntitiesToCreate();

	/* Usuniêcie martwych jednostek */
	for (_iterGameObj it = _depthBuffer["FG"].begin(); it != _depthBuffer["FG"].end(); ){

		EntityPtr tmpEntity = std::dynamic_pointer_cast< Entity >(*it);
		if( tmpEntity) {

			PlayerPtr player = std::dynamic_pointer_cast< Player >(*it);

			if (!player && !tmpEntity->isAlive())
					it = _depthBuffer["FG"].erase(it);
			else 
				++it;
		}
	}

}

void GameSupervisor::sleepAndAddEnities() {
	int distance = al_get_display_width(al_get_current_display());
	list<LevelEntityData> & ents = _mapView->getLevel().getEntitiesToCreate();

	/* Deaktywacja jedostek, które s¹ znacz¹co poza zasiêgiem widoku gracza z listy jednostek aktywnych */
	for (_iterGameObj it = _depthBuffer["FG"].begin(); it != _depthBuffer["FG"].end(); ){

		EntityPtr tmpEntity = std::dynamic_pointer_cast< Entity >(*it);
		if( tmpEntity) {

	
			if (typeid(*tmpEntity) == typeid(class Flag) ||
				typeid(*tmpEntity) == typeid(class Player)) {
					++it;
					continue;
			}

			if (( tmpEntity->getXOnMap() + distance < mario->getXOnMap() ) || 
				( tmpEntity->getXOnMap() - distance > mario->getXOnMap() )) {
							
						


					/* dodanie jednostki do listy oczekuj¹cych (bêd¹cych poza zasiêgiem)*/
					LevelEntityData tmp;
					if (typeid(*tmpEntity) == typeid(class GoombaEntity))
						tmp._id = goomba;
					
					if (typeid(*tmpEntity) == typeid(class Coin))
						tmp._id = coin;

					tmp._x = tmpEntity->getXOnMap();
					tmp._y = tmpEntity->getNextYOnScreen();

					ents.push_back(tmp);

					/* usuniêcie  jednostki z listy aktywnych */
					it = _depthBuffer["FG"].erase(it);
			}
			else {
				++it;
			}
		}
	}

 
    /* Dodanie jednostek które s¹ w zasiêgu gracza */
    for (std::list<LevelEntityData>::iterator it = ents.begin(); it != ents.end(); ){
        if ( ( mario->getXOnMap() - distance < it->_x ) &&
			 ( mario->getXOnMap() + distance > it->_x ) ) {

            GameObjectPtr e = Engine::get().entityFactory()->createEntity(*it);
			_depthBuffer["FG"].push_back(e);
			it = ents.erase(it);
        } 
		else {
			++it;
		}
	}
}

void GameSupervisor::checkPlayerEntitiesCollisions() {

	// poziomy i pionowy aabb gracza w nastêpnym 'kroku'
	Aabb pBoxX = mario->getNextHorizontalAabb();
	Aabb pBoxY = mario->getNextVerticalAabb();

	for (_iterGameObj it = _depthBuffer["FG"].begin(); it != _depthBuffer["FG"].end(); ++it ){

		if(typeid(**it) == typeid(class Player) )
			continue;

		/* wy³apanie jednostki flaga, w celu osobnej aktualizacji podczas stanu WIN */
		if( !_ptrFlag)
			_ptrFlag = std::dynamic_pointer_cast< Flag > (*it);

		EntityPtr tmpEntity = std::dynamic_pointer_cast< Entity >(*it);


		Aabb eBox = tmpEntity->getAabb();

		/* sprawdzanie czy nast¹pi³a kolizja. Je¿eli tak to obiekt gracza decyduje co dalej*/

		if ( pBoxY.isOver(eBox) ) {
			mario->collisionUnderPlayer(tmpEntity);
			pBoxY = mario->getNextVerticalAabb();
		}
		else if ( pBoxX.isOnLeft(eBox) ) {
			mario->forbidMoveRight();
			mario->collisionOnRight(tmpEntity);
			pBoxX = mario->getNextHorizontalAabb();
		}
		else if ( pBoxX.isOnRight(eBox) ) {
			mario->forbidMoveLeft();
			mario->collisionOnLeft(tmpEntity);
			pBoxX = mario->getNextHorizontalAabb();
		}
		else if ( pBoxY.isUnder(eBox) ) {
			mario->collisionOverPlayer(tmpEntity);
			pBoxY = mario->getNextVerticalAabb();
		}

	}

}
/**
	Metody publiczne
*/

void GameSupervisor::gameLoop() {

	while (!_isDone){

		ALLEGRO_EVENT ev;
		al_wait_for_event(_eventQueue, &ev);
		
		/* obs³uga zdarzeñ wejœciowych ( aktualnie tylko klawiatura )*/
		processEvents(ev);
		
		/* aktualizacja stanu gry */
		gameUpdate(ev);
	
		/* rysowanie aktualnej rozgrywki na ekranie */
		render();
	}

};





//================================================
// Œmieci - ju¿ nie aktualne ale mo¿e siê przydaæ
//================================================

//BEGIN PROJECT RENDER================
/*if (state == TITLE)
{
titleScreen->Render();
}
else if (state == PLAYING)
{
al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "Player has %i lives left. Player has destroyed %i objects",
ship->GetLives(), ship->GetScore());

for (iter = objects.begin(); iter != objects.end(); ++iter)
(*iter)->Render();
}
else if (state == LOST)
{
lostScreen->Render();
}
*/