#include "EntityFactory.h"


/**
	Konstruktory & destruktor
*/
EntityFactory::EntityFactory(void){};
EntityFactory::~EntityFactory(void){};

/** 
	Metody publiczne
*/
GameObjectPtr EntityFactory::createEntity(LevelEntityData entity){
	GameObjectPtr tmp;

	if( entity._id == goomba )
		tmp.reset(new GoombaEntity(entity._x, entity._y) );
	
	if( entity._id == coin ) 
		tmp.reset ( new Coin(entity._x, entity._y) );
		
	if( entity._id == flag ) 
		tmp.reset ( new Flag(entity._x, entity._y) );
		
	if( !tmp )
		throw cannotCreateEntity(entity._id);

	return tmp;
};