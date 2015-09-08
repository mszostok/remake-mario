#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <memory>

#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>


#include "GameObject.h"
#include "Sprite.h"
#include "Map.h"
#include "Aabb.h"

using namespace std;
using namespace player;
using namespace mapSpace;

class Entity : public GameObject {

protected:

	vector<player::State> _state;	  // stan, w kt�rym znajduje si� jednostka	
	Sprite _left;				     // animacja - posta� idzie w lewo
	Sprite _right;                  // animacja - posta� idzie w prawo

	double _x;                    // po�o�enie jednostki na osi OX na ekranie ( s�u�y do wy�wietlania )
	double _xOnMap;				 // po�o�enie jednostki na osi OX na mapie poziomu ( s�u�y do wykrywania kolizji )
	double _y;                  // po�o�enie jednostki na osi OY
	double _velX;              // pr�dko�� na osi OX
	double _velY;             // pr�dko�� na osi OY
	double _gravity;         // si�a grawitacji     
	double _drag;		    // si�a oporu powietrza ( im mniejsza tym wi�kszy op�r )
	double _offset;		   // offset - synchronizacja jednostki z map� kt�ra si� przesuwa
	double _ax;			  // przy�pieszenie jednostki na osi OX

	bool _isOnGround;     // czy jednostka jest na pod�o�u
	bool _canLeft;       // czy jednostka mo�e i�� w lewo
	bool _canRight;     // czy jednostka mo�e i�� w prawo
	bool _upgrade;	   // czy jednostka jest powi�kszona
	bool _isAlive;	  // czy jednostka �yje
	bool _isKilled;

	int _cnt;
	size_t _lifes;	// liczba �y� do wykorzystania

public:
	Entity(double x, double y);
	~Entity(void);

	/* Poruszanie postaci� */
	virtual void moveLeft() { _velX = defaultXLeftVelocityEntity;  	_state[Horizontal] = player::goLeft;   };
	virtual void moveRight() { _velX = defalutXRightVelocityEntity; 	_state[Horizontal] = player::goRight;  };
	
	void negateXVelocity() { _velX = -_velX; };

	void stay();
	virtual void fall();

	/* Ustalanie stanu */
	void forbidMoveLeft() { _canLeft = false; };
	void forbidMoveRight() { _canRight = false; };

	virtual void setDefaultMovement();

	virtual void playerOnGround() { _velY = 0.0; _isOnGround  = true;  _state[Vertical] = stand; };

	virtual void checkLoseLife();

	void kill(){ _isKilled = true; };

	/* Wykrywanie kolizji AABB */
	bool isAnyFieldBelowMe(Level &lvl);
	bool isAnyFieldAboveMe(Level &lvl);
	bool isAnyFieldOnLeft(Level &lvl);
	bool isAnyFieldOnRight(Level &lvl);

	virtual void checkCollisionsWithLevel(Level &lvl);

	/* Gettery */
	double getXOnMap() const { return _xOnMap; };
	double getNextXOnMap() const { return _xOnMap + _velX + _ax; };

	virtual double getXOnScreen() const { return _x - _offset; };
	double getYOnScreen() const { return _y; };
	double getNextXOnScreen() const { return _x + _velX + _ax; };
	double getNextYOnScreen() const { return _y + _velY; };

	size_t getLifes() const { return _lifes; };
	bool isAlive() const { return _isAlive; };
	
	Aabb getNextVerticalAabb() const {
        Aabb box(_xOnMap - static_cast<int>(_velX), getNextYOnScreen(), tileWidth - 6 , (tileHeight + _upgrade * tileHeight) - 3 );
		return box;
    };
	Aabb getNextHorizontalAabb() const {
		Aabb box(getNextXOnMap(), _y, tileWidth, (tileHeight + _upgrade * tileHeight) - 3);
        return box;
    };
	virtual Aabb getAabb() const {
		Aabb box(_xOnMap - static_cast<int>(_velX), _y, tileWidth - 6, (tileHeight + _upgrade * tileHeight) - 3);
        return box;
    };

	/* Modyfikatory */
	void initSprites(string name );

	virtual void draw();
	virtual void update(Map &map);
};


typedef std::shared_ptr < Entity > EntityPtr;

#endif