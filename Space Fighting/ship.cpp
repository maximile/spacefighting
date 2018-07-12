#include "ship.hpp"

Ship::Ship() {
}

Ship::Ship(sf::Image image) {
    _texture.loadFromImage(image);
    _sprite = sf::Sprite(_texture);
    _collisionMask = CollisionMask(image);
    
//    setPos(100, 100);
}

CollisionMask Ship::getCollisionMask() {
    return _collisionMask;
}

sf::Sprite Ship::getSprite() {
    return _sprite;
}

void Ship::setPos(float x, float y) {
    _pos = sf::Vector2f(x, y);
    _sprite.setPosition(x, y);
}

void Ship::applyInputDirection(int x, int y) {
    if (x != 0) _inputX = x;
    if (y != 0) _inputY = y;
}

void Ship::releaseInputDirection(int x, int y) {
    if (x != 0) _inputX = 0;
    if (y != 0) _inputY = 0;
}

void Ship::step(int delta) {
    _vel.x = _vel.x + (_inputX * 0.1);
    _vel.y = _vel.y + (_inputY * 0.1);

    float x = getPos().x + _vel.x;
    float y = getPos().y + _vel.y;
    setPos(x, y);
}

sf::Vector2f Ship::getPos() {
    return _pos;
}

