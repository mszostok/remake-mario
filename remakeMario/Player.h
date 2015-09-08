#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include <exception>
#include <memory>

#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>

#include "Entity.h"
#include "Coin.h"
#include "Flag.h"

using namespace player;

class Player : public Entity{

	double _achievedXMulByTileWidth;  // wielokrotnoœæ szerokoœci pojedyñczego kafla przebytej drogi
	double _velXBackup;

	int _halfVisibleAreaWidth;		// po³owa widocznego obszaru
	size_t _levelWidth;			   // szerokoœæ poziomu

	bool _platformRightEnd;		 // czy jesteœmy ju¿ na koñcu platformy
	bool _jumpAllowed;			// czy gracz mo¿e skakaæ 
	bool _animation;
	bool _isWin;

	int _score;

public:
	Player(double x, double y, size_t width);
	~Player();

	/* Poruszanie postaci¹ */
	virtual void moveLeft() { _velX = defaultXLeftVelocity;  	_state[Horizontal] = player::goLeft;   };
	virtual void moveRight() { _velX = defalutXRightVelocity; 	_state[Horizontal] = player::goRight;  };
	
	void  setXAcceleration(double ac)     { _ax = ac * static_cast<int>(_velX*5/7); }

	void jump(double yVelocity = player::defaultYVelocity);
	void fall();

	/* Ustalanie stanu */
	void setDefaultMovement();

	void playerOnGround();

	void allowToJump() { _jumpAllowed = true; };
	void forbidToJump() { _jumpAllowed = false; };

	void checkLoseLife();
	void respawn();

	void checkCollisionsWithLevel(Level &lvl);

	void collisionUnderPlayer(EntityPtr entity);	
	void collisionOverPlayer(EntityPtr entity);
	void collisionOnRight(EntityPtr entity);
	void collisionOnLeft(EntityPtr entity);


	/* Gettery */
	double getAchievedXMulByTileWidth() const { return _achievedXMulByTileWidth; }
	double getDeltaXToNextTileWidth();

	double getVelX() const {
		if (_xOnMap <= 495 || _platformRightEnd || !_canLeft || !_canRight) 	return 0;

		return _velX; 
	};

	double getXOnScreen() const { return _x; };
	
	int getScore() const { return _score; };

	bool isWin() const { return _isWin; };
	/* Modyfikatory */
	void resetAnimation() { _animation = false; _gravity = defaultGravity;};

	void draw();
	void update(Map &map);
};

typedef std::shared_ptr < Player > PlayerPtr;
#endif