#include "Entity.h"
#include "Engine.h"
/**
	konstruktor & destruktor
*/
Entity::Entity(double x, double y) 
	: _state(player::stand), _x(x), _xOnMap(x), _y(y), _velX(0), _velY(0), _gravity(player::defaultGravity), _isOnGround(false), _canLeft(true), 
	  _canRight(true), _drag(1),_lifes(5), _offset(0), _isAlive(true), _isKilled(false), _cnt(0), _ax(0) { };

Entity::~Entity(void){}


/**
	Poruszanie jednostk¹
*/
void Entity::stay(){

	if (_state[Horizontal] == goRight)
		_state[Horizontal] = stayRight;
	else if (_state[Horizontal] == goLeft)
		_state[Horizontal] = stayLeft;

	_velX = 0;
}

void Entity::fall(){
	_state[Vertical] = player::fall;
	_velY =  0;
	_isOnGround = false;
};


/**
	Ustalanie stanu
*/
void Entity::setDefaultMovement()  {
	_isOnGround = false;
	_canRight = _canLeft = true;
}

void Entity::checkLoseLife() {
	if (_y > 590)
		--_lifes;

	if( _lifes <= 0)
		_isAlive = false;
}

/**
	Wykrywanie kolizji AABB
*/
bool Entity::isAnyFieldBelowMe(Level &lvl){

	int curr_x_tile = _xOnMap / mapSpace::tileWidth;
	int curr_y_tile = _y / mapSpace::tileHeight;
    for (int x = 0; x < 2; ++x) {

        if (lvl.field(curr_x_tile + x, curr_y_tile + 1 + _upgrade) == mapSpace::none) 
            continue;

        Aabb fieldAabb = lvl.getFieldAabb(curr_x_tile + x, curr_y_tile + 1 + _upgrade);

        if (getNextVerticalAabb().isOver(fieldAabb)){
            _y = fieldAabb._minY - (tileHeight + tileHeight * _upgrade -3 );
			return true;
		}

    }
    return false;
};

bool Entity::isAnyFieldAboveMe(Level &lvl) {
	int curr_x_tile = _xOnMap / mapSpace::tileWidth;
	int curr_y_tile = _y / mapSpace::tileHeight;
    for (int x = 0; x < 2; ++x) {

        if (lvl.field(curr_x_tile + x, curr_y_tile - 1 ) == mapSpace::none) 
            continue;

        Aabb fieldAabb = lvl.getFieldAabb(curr_x_tile + x, curr_y_tile - 1);

        if (getNextVerticalAabb().isUnder(fieldAabb))
            return true;

    }
    return false;
}

bool Entity::isAnyFieldOnLeft(Level &lvl) {
    int curr_x_tile = _xOnMap / mapSpace::tileWidth;
	int curr_y_tile = _y / mapSpace::tileHeight;

    for (int y = -1; y < 1; ++y) {
        if (lvl.field(curr_x_tile - 1, curr_y_tile + y + _upgrade) == mapSpace::none) 
            continue;
        
        Aabb fieldAabb = lvl.getFieldAabb(curr_x_tile - 1, curr_y_tile + y + _upgrade);

        if (getNextHorizontalAabb().isOnRight(fieldAabb)) 
            return true;

    }
    return false;
}

bool Entity::isAnyFieldOnRight(Level &lvl) {
    int curr_x_tile = _xOnMap / mapSpace::tileWidth;
	int curr_y_tile = _y / mapSpace::tileHeight;

	
    for (int y = -1; y < 1; ++y) {
        if (lvl.field(curr_x_tile + 1, curr_y_tile + y + _upgrade) == mapSpace::none) 
            continue;
        
        Aabb fieldAabb = lvl.getFieldAabb(curr_x_tile + 1, curr_y_tile + y + _upgrade);

        if (getNextHorizontalAabb().isOnLeft(fieldAabb)) 
            return true;

    }
    return false;
}

void Entity::checkCollisionsWithLevel(Level &lvl) {
    
	if (!isAnyFieldBelowMe(lvl))
		int a = 0 ;
	// czy jednostka koliduje z czymœ od do³u
    if (isAnyFieldBelowMe(lvl))
        playerOnGround();

	// czy jednostka koliduje z czymœ od góry
    if(isAnyFieldAboveMe(lvl))
        fall();

	// czy jednostka koliduje z czymœ po lewej stronie
    if (isAnyFieldOnLeft(lvl)) 
        moveRight();
    
	// czy jednostka koliduje z czymœ po prawej stronie
    if (isAnyFieldOnRight(lvl))
        moveLeft();

};


/**
	Modyfikatory
*/
void Entity::initSprites(string name){
		_left.setPattern(Engine::get().spriteDatabase()->get(name + "Left"));
		_right.setPattern(Engine::get().spriteDatabase()->get(name + "Right"));
}

void Entity::update(Map &map) {

	setDefaultMovement();

	checkCollisionsWithLevel(map.getLevel());

	_offset = map.getOffsetToEntity();

	if (!_isOnGround) {    // wylicz now¹ prêdkoœæ oraz po³ó¿enie na osi OY
		_y = getNextYOnScreen();
		_velY += _gravity;
	}

	checkLoseLife();

	if(_isKilled) {
		++_cnt;
		_state[Vertical] = jump;

		if(_cnt >= 3)
			--_lifes;
	}
	if (_canLeft && _canRight && !_isKilled) { // wylicz pozycjê gracza w poziomie (oœ OX).
			_x = getNextXOnScreen();
			_xOnMap = getNextXOnMap();
	}

	switch (_state[Horizontal]){



	case player::stayRight: 
	case player::goRight: _right.update(_state);
		break;
	case player::stayLeft:
	case player::goLeft: _left.update(_state);
		break;

	default:
		break;
	}

}

void Entity::draw() {

	switch (_state[Horizontal]) {

	case player::stayRight:
	case player::goRight: _right.drawCurrentFrame( getXOnScreen(), _y);
		break;

	case player::stayLeft:
	case player::goLeft: _left.drawCurrentFrame( getXOnScreen(), _y);
		break;

	};

};