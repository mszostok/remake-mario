#include "Player.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


/**
	konstruktor & destruktor
*/
Player::Player(double x, double y, size_t width) 
	: Entity(x,y), _achievedXMulByTileWidth(x),  _levelWidth(width), _platformRightEnd(false), _jumpAllowed(false), _animation(false), 
	_isWin(false), _score(0) {

	initSprites("mario");
	_upgrade = false;

	_state[Vertical] = player::stand;
	_state[Horizontal] = player::stayRight;

	_halfVisibleAreaWidth = al_get_display_width(al_get_current_display()) / 2 - mapSpace::tileWidth; // połowa ekranu - szerokość gracza
}

Player::~Player(){}


/**
	Poruszanie graczem
*/
void Player::jump(double y_velocity) {
	static int call = 0;
	static bool superJump = false;

	if (_jumpAllowed) {						  // wykonaj skok o ile jest taka możliwość
		superJump = true;
		call = 1;

		_state[Vertical] = player::jump;
		_jumpAllowed = false;
		_isOnGround = false;
		_velY = y_velocity;
	
		if( y_velocity != -5)
		if (_velX == 0)
			_drag = 0.7;
		else						    // jeśli mamy już jakąś prędkość to wytracamy ją w powietrzu powoli
			_drag = 0.8;


	}

	if (!_jumpAllowed && superJump)  // zliczanie wejścia do funkcji podczas skoku i nie wykorzystanym super skoku
		++call;
	if (superJump && call > 8){     // wykorzystanie super skoku
		_velY += 0.5*y_velocity;
		superJump = false;
	}

}

void Player::fall(){
	Entity::fall();

	_jumpAllowed = false;
}

/**
	Ustalanie stanu
*/
void Player::setDefaultMovement()  {
	Entity::setDefaultMovement();

	_jumpAllowed = false;
	//_velX /= _drag;
}

void Player::playerOnGround(){
	Entity::playerOnGround();

	_jumpAllowed = true;
}

void Player::checkLoseLife(){
	static size_t startY = 0;

	if( _animation ) {
		forbidMoveLeft();
		forbidMoveRight();
	}
		
	// jeżeli poniżej ostatniego kafla, to traci życie
	if (_y > 590) {
		
		if( _animation ) {	// sprawdzenie czy kolejne wejscie do funkcji nastąpiło podczas animacji
			respawn();	   // ustawienie postaci na początku mapy
			_animation = false;	
		}
		else {
			_state[Vertical] = player::jump;
			_velY = 0;
			startY = _y;						 // potrzebne do dy
			_y -= 15;
			_gravity = -2 * defaultGravity;		// odwrócenie grawitacji, zapewni unoszenie się postaci
			_animation = true;
		}
	}

	if( _animation && startY - _y >= 45 ) // dy, jeśli różnica jest większa niż 45 to ustawienie normalnej grawitacji
		_gravity = defaultGravity;

	if( _lifes <= 0)
		_isAlive = false;
}

void Player::respawn(){
	if( _upgrade){
		_upgrade = false;
		initSprites("mario");
		_score = 0;
	}

	--_lifes;
	_achievedXMulByTileWidth =_xOnMap = _x = 45;
	_y = 100;
	_velX = 0; 
	_velY = 0;
	_state[Horizontal] = player::goRight;

};

void Player::checkCollisionsWithLevel(Level &lvl) {
    
	// czy jednostka koliduje z czymś od dołu
    if (!_isOnGround && isAnyFieldBelowMe(lvl)){
		_drag = 1;
		playerOnGround();
	}

	// czy jednostka koliduje z czymś od góry
    if(isAnyFieldAboveMe(lvl))
        fall();

	// czy jednostka koliduje z czymś po lewej stronie
    if (isAnyFieldOnLeft(lvl)) 
        forbidMoveLeft();
    
	// czy jednostka koliduje z czymś po prawej stronie
    if (isAnyFieldOnRight(lvl))
        forbidMoveRight();

};

void Player::collisionUnderPlayer(EntityPtr entity){
	CoinPtr tmpCoin = std::dynamic_pointer_cast< Coin > (entity);
	FlagPtr tmpFlag = std::dynamic_pointer_cast< Flag > (entity);
	if( tmpCoin ){
		_score += tmpCoin->collect();
	}
	else if( tmpFlag ){
		_isWin = true;
	}
	else {
		_score += 2;
		allowToJump();
		jump(-5);
		entity->kill();
	}

};

void Player::collisionOverPlayer(EntityPtr entity){
	CoinPtr tmpCoin = std::dynamic_pointer_cast< Coin > (entity);
	FlagPtr tmpFlag = std::dynamic_pointer_cast< Flag > (entity);

	if( tmpCoin ){
		_score += tmpCoin->collect();
	}
	else if( tmpFlag ){
		_isWin = true;
	}
	else 
	respawn();
}

void Player::collisionOnRight(EntityPtr entity){
	CoinPtr tmpCoin = std::dynamic_pointer_cast< Coin > (entity);
	FlagPtr tmpFlag = std::dynamic_pointer_cast< Flag > (entity);
	if( tmpCoin ){
		_score += tmpCoin->collect();
	}
	else if( tmpFlag ){
		_isWin = true;
		allowToJump();
		jump(-5);
	}
	else 
	respawn();

};

void Player::collisionOnLeft(EntityPtr entity){
	CoinPtr tmpCoin = std::dynamic_pointer_cast< Coin > (entity);
	FlagPtr tmpFlag = std::dynamic_pointer_cast< Flag > (entity);
	if( tmpCoin ){
		_score += tmpCoin->collect();
	}
	else if( tmpFlag ){
		_isWin = true;
	}
	else 
	respawn();
};


/**
	Gettery 
*/
double Player::getDeltaXToNextTileWidth(){

	double dx = _achievedXMulByTileWidth - _xOnMap;
	int tileWidth = static_cast<int> (mapSpace::tileWidth);
	int halfVisibleAreaWidth = al_get_display_width(al_get_current_display()) / 2;

	if (_xOnMap <=  halfVisibleAreaWidth - tileWidth){ // lewa strona platformy 
		int i = _xOnMap / tileWidth;
		_achievedXMulByTileWidth = i * tileWidth;
		return 0;
	}

	if (_xOnMap >= (_levelWidth - 12) * tileWidth){ // prawa strona platformy 
		int i = _xOnMap / tileWidth;
		_achievedXMulByTileWidth = i * tileWidth;
		return -tileWidth;
	}
	if (dx <= -tileWidth){ // zwracanie dx jeœli idziemy w prawo
		_achievedXMulByTileWidth += tileWidth;
		return 0;
	}
	if (dx >= tileWidth){ // zwracanie dx jeœli idziemy w lewo
		_achievedXMulByTileWidth -= tileWidth;
		return 0;
	}
	return dx;
}


/**
	Modyfikatory
*/

void Player::draw() {

	switch (_state[Horizontal]) {

	case player::stayRight:
	case player::goRight: _right.drawCurrentFrame( _x, _y);
		break;

	case player::stayLeft:
	case player::goLeft: _left.drawCurrentFrame( _x, _y);
		break;

	};

};

void Player::update(Map &map){

	setDefaultMovement();

	checkCollisionsWithLevel(map.getLevel());

	if (!_isOnGround) {    // wylicz nową prędkość oraz połóżenie na osi OY
		_velX *= _drag;   // zmniejszenie (opór)
		_y = getNextYOnScreen();
		_velY += _gravity;
	}
	
	checkLoseLife();

	if (_canLeft && _canRight) { // wylicz pozycję gracza w poziomie (oś OX).
			_x = getNextXOnScreen();
			_xOnMap = getNextXOnMap();


		if ((_levelWidth - static_cast<int>(_xOnMap / 45)) <= 11)
			_platformRightEnd = true;
		else
			_platformRightEnd = false;

		if (_x < 0) { // nie można wyjść za początek mapy
			_xOnMap = _x = 0;
		}
		else if (_x >= 990 - mapSpace::tileWidth){ // nie można wyjść za koniec mapy
			_x = 990 - mapSpace::tileWidth;
			_xOnMap = _levelWidth * 45;
		}
		else if ((_xOnMap >= _halfVisibleAreaWidth) && !_platformRightEnd) {// nie można wyjść za prawą krawędź mapy		
			// nalezy przesunąć kamere (mape) o pozycję gracza (gracz będzie na srodku ale stworzymy iluzję że się przemieszcza)
			_x =_halfVisibleAreaWidth;
		}
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



