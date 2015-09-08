#ifndef LEVEL_H
#define LEVEL_H

#include <exception>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>

#include "GameObject.h"
#include "Aabb.h"

using namespace std;
using namespace mapSpace;



//==============================================
// SpriteConfigPattern
//==============================================
/* wzorzec dotycz¹cy podstawowych w³asnoœci obiektu Entity*/
struct LevelEntityData {
    int _id;  
    double _x;          
    double _y;          

	LevelEntityData() :  _id(-1), _x(-1), _y(-1) {};

    LevelEntityData(const int& id, double x, double y)
        :  _id(id), _x(x), _y(y) {};
};

bool compX(const LevelEntityData& a, const LevelEntityData& b);

//==============================================
// Level
//==============================================
/* Klasa wyj¹tku */
class FileNotFound : public exception{
	string _exceptionName;
public:
	FileNotFound(string name) : _exceptionName("File not found: " + name +".lvl") {};
	virtual const char* what() const throw() {
		return _exceptionName.c_str();
	}
};

/* obiekt tej klasy reprezentuje aktualnie wczytany poziom gry*/
class Level {
		
		size_t _width;		// szerokoœæ wczytanego poziomu
		size_t _height;	   //  wysokoœæ wczytanego poziomu

		list<LevelEntityData> _entitiesToCreate;	// lista jednostek do stworzenia
		vector<vector<TilesType>> _level;	       // tablica dwuwymiarowa przechowuj¹ca poziom


public:
		Level(void);
		~Level(void);

		/* Modyfikatory */
		void loadFromFile(const string& filename); 
		void addEntity(int &value, const size_t & x, const size_t & y);

		/* Gettery */
		TilesType field(size_t x, size_t y) const; 
		Aabb getFieldAabb(double x, double y) const;

		size_t getWidth() const   { return _width; }
		size_t getHeight() const  { return _height; }

		list<LevelEntityData> & getEntitiesToCreate() { return _entitiesToCreate; };
};


#endif