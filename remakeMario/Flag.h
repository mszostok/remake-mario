#ifndef FLAG_H
#define FLAG_H

#include <memory>

#include "Entity.h"
#include "Sprite.h"

class Flag : public Entity{

	Sprite _pipe;		// sprite masztu
	Sprite _flag;	   // sprite flagi - akutalnie moneta

	double _heightOffset;	// ró¿nica pomiêdzy odleg³oœci¹ koñca masztu od monety

public:
	Flag(double x, double y);
	~Flag(void);

	/* Gettery */
	Aabb getAabb() const {
		Aabb box(_x, _y, 45, 8 * 35);
        return box;
    };

	/* Modyfikatory */
	void update(Map &map);
	void draw();
	void initSprite();
	bool setWin();

	int collect() { _isAlive = false; return 1; };
};

typedef std::shared_ptr < Flag > FlagPtr;
#endif



