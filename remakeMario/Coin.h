#ifndef COIN_H
#define COIN_H

#include <memory>

#include "Entity.h"
#include "Sprite.h"


class Coin : public Entity {

	Sprite _coin;
	
public:
	Coin(double x, double y);
	~Coin(void);

	/* Gettery */
	Aabb getAabb() const {
		Aabb box(_x, _y, 45, 35);
        return box;
    };

	/* Modyfikatory */
	void update(Map &map);
	void draw();
	void initSprite();

	int collect() { _isAlive = false; return 1; };
};


typedef std::shared_ptr < Coin > CoinPtr;
#endif