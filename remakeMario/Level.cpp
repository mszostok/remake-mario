#include "Level.h"




bool compX(const LevelEntityData& a, const LevelEntityData& b) {
        return a._x < b._x;
}

//==============================================
// Level
//==============================================
/**
	Konstruktory & destruktor
*/
Level::Level(void): _width(0), _height(0){}
Level::~Level(void){}


/**
	Metody publiczne
*/

/* Modyfikatory */
void Level::loadFromFile(const string& filename) {



	ifstream lvl("data/levels/"+filename+".lvl", ifstream::in);

	if (!lvl.is_open()) 
		throw FileNotFound(filename);

	_level.clear();
	string line;

	int value;
	char val2 = 'b';
	size_t x = 0, y = 0;
	/* Wczytywanie mapy poziomu oraz jednostek znajduj¹cych siê na mapie. 
	   Jednostki zostaj¹ za³adowane do listy i zast¹pione pustymi polami */
	while ( !lvl.eof() ) {

		getline(lvl, line);
		
		istringstream ssline(line);
		vector<TilesType> tmp;
		x = 0;
		while (!ssline.eof() && ssline.rdbuf()->in_avail()){
			if(	(ssline >> value ) ) {
				addEntity(value, x, y);
				tmp.push_back(TilesType(value));
				++x;
			}
			else {
				ssline.clear();
				ssline >> val2;
				value = val2;
				addEntity(value, x, y);
				if( value < 0 || value >= TilesType::CNT )
					value = 0;
				tmp.push_back(TilesType(value));
				++x;
			}
		}

		if (!tmp.empty())
		_level.push_back(tmp);
		++y;
	}

	/* Sprawdzanie poprawnej d³ugoœci poziomu - obcinanie wierszy wystaj¹cych */
	_height = _level.size();
	_width = _level.at(0).size();
	for (vector<vector<TilesType>>::iterator it = _level.begin(); it != _level.end(); ++it) {
		if (it->size() < _width)
				_width = it->size();
	}


	/* Posortowanie jednostek wed³ug rosn¹cych wartoœci x */
	_entitiesToCreate.sort(compX);
}

void Level::addEntity(int &value, const size_t & x, const size_t & y){

	if( value == goomba || value == coin || value == flag){
		LevelEntityData tmp(value, x * tileWidth, y *tileHeight);
		value = none;
		_entitiesToCreate.push_back(tmp);
	}

}

/* Gettery */
TilesType Level::field(size_t x, size_t y) const {
	if (x >= _width || y >= _height) { // je?li pole poza map? to zwracamy none;
		return none;
	}
	return _level.at(y).at(x);
}

Aabb Level::getFieldAabb(double x, double y) const {

    Aabb box = Aabb(x*tileWidth, y*tileHeight, tileWidth, tileHeight);
    return box;
}