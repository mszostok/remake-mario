#ifndef AABB_H
#define AABB_H


#include "GameObject.h"
/*	Klasa stworzona do wykrywania kolizji metod� . */
class Aabb {
public:
    double _minX;		    // lewy g�rny wierzcho�ek
    double _minY;

	double _maxX;		  // prway dolny wierzcho�ek
    double _maxY;

	size_t _height;		//  rozmiar prostok�ta
	size_t _width;

public:
	Aabb(double x, double y, size_t height, size_t widht);
	~Aabb();

	
	/* Sprawdzanie stanu*/
	bool collides(const Aabb& snd) const;			// czy prostok�ty si� przecinaj�
    bool isOver(const Aabb& snd) const;			   // czy this jest powy�ej snd
    bool isUnder(const Aabb& snd) const;		  // czy this jest poni�ej snd
    bool isOnLeft(const Aabb& snd) const;		 // czy this jest po lewej stronie snd
    bool isOnRight(const Aabb& snd) const;		// czy this jest po prawej stronie snd

	/* Gettery */
    double getMinX() const { return _minX; }
    double getMinY() const { return _minY; }
    double getMaxX() const { return _maxX; }
    double getMaxY() const { return _maxY; }
	
	/* Settery */
    Aabb Move(int xPosition, int yPosition);
};




#endif // !AABB_H
