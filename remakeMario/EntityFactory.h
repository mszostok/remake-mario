#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <memory>
#include <exception>
#include <string>

#include "GameObject.h"
#include "Level.h"
#include "GoombaEntity.h"
#include "Coin.h"
#include "Flag.h"

using namespace std;

/* klasa wyj�tk�w */
class cannotCreateEntity : public exception {
	string _exceptionName;
public:
	cannotCreateEntity(int name) : _exceptionName("Factory cannot create entity id: " + std::to_string(name)) {};
	virtual const char* what() const throw() {
		return _exceptionName.c_str();
	}
};

/* implementacja fabryki wytwarzaj�cej jednostki */
class EntityFactory {
public:
	EntityFactory(void);
	~EntityFactory(void);

	/* metoda zwracaj�ca zadan� jednostk� */
	GameObjectPtr createEntity(LevelEntityData entity);
};

typedef std::shared_ptr < EntityFactory > EntityFactoryPtr;
#endif

