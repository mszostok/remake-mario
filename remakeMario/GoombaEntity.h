#ifndef GOOMBAENTITY_H
#define GOOMBAENTITY_H

#include <memory>

#include "Entity.h"

class GoombaEntity : public Entity {

public:
	GoombaEntity(double x, double y);
	~GoombaEntity(void);
};

typedef std::shared_ptr < GoombaEntity > GoombaEntityPtr;
#endif