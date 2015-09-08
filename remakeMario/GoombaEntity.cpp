#include "GoombaEntity.h"


/**
	Konstruktory & destruktor
*/
GoombaEntity::GoombaEntity(double x, double y) : Entity(x, y) {
	/* inicjalizacja */
	_lifes = 1;
	initSprites("goomba");
	_upgrade = false;

	_state[Vertical] = player::stand;
	_state[Horizontal] = player::goLeft;

	/* ustawienie pocz�tkowej pr�dko�ci w lew� stron� */
	moveLeft();
};
GoombaEntity::~GoombaEntity(void){}