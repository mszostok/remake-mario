#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>

namespace player{
	enum State{ Horizontal, Vertical,stand = 32, goLeft, goRight, stayLeft, stayRight, jump, fall };
	const double defaultYVelocity = -10;
	const double defaultGravity   = 0.45;
	const double defaultXLeftVelocity  = -5;
	const double defalutXRightVelocity =  5;
	const double defaultXLeftVelocityEntity  = -1;
	const double defalutXRightVelocityEntity =  1;
}

namespace mapSpace{ // +Space - aby nie by³o konflitku nazw
	enum TilesType{none = 0, ground, block, blockRightEnd, blockLeftEnd, pipeLeftBottom, pipeRightBottom, pipeLeftTop, pipeRightTop, brick,  CNT };
	enum EntityID { goomba = 'g', coin = 'c', flag = 'f'};
	const size_t tileWidth = 45;
	const size_t tileHeight = 35;

}
class GameObject{
public:
	GameObject();
	~GameObject();

	virtual void update() {};
	virtual void draw()	{};
};

typedef std::shared_ptr < GameObject > GameObjectPtr;
#endif