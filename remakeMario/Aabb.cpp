#include "Aabb.h"

/**
	Konstruktor & destruktor
*/

Aabb::Aabb(double x, double y, size_t width, size_t height): _minX(x), _minY(y), _height(height), _width(width){
	_maxX = _minX + _width;
	_maxY = _minY + _height;
}
Aabb::~Aabb(){}

/*
	Metody publiczne
*/


/* Sprawdzanie stanu */
bool Aabb::collides(const Aabb& snd) const {
	if ( _minX > snd.getMaxX() || _maxX < snd.getMinX() || _minY > snd.getMaxY() || _maxY < snd.getMinY() ) {
		return false;
	};
	return true;
};

bool Aabb::isOver(const Aabb& snd) const {
	return collides(snd) && // czy wogóle siê przecinaj¹
		snd.getMinY() < _maxY && snd.getMinY() > _minY;
};

bool Aabb::isUnder(const Aabb& snd) const {
	return snd.isOver(*this);
};

bool Aabb::isOnLeft(const Aabb& snd) const{
	return collides(snd) &&
		snd.getMinX() > _minX && snd.getMinX() < _maxX;
};

bool Aabb::isOnRight(const Aabb& snd) const{
	 return snd.isOnLeft(*this); // czyli czy box jest na lewo od this
};


/* Settery */
Aabb Aabb::Move(int xPosition, int yPosition) {
	_minX = xPosition;
	_minY = yPosition;

	_maxX = _minX + _width;
	_maxY = _minY + _height;
	return *this;
}