#include "ship.hpp"

Ship::Ship() {
}

Ship::Ship(sf::Image image) {
    _texture.loadFromImage(image);
    _sprite = sf::Sprite(_texture);
    _collisionMask = CollisionMask(image);
    
    setPos(100, 100);
}

CollisionMask Ship::getCollisionMask() {
    return _collisionMask;
}

sf::Sprite Ship::getSprite() {
    return _sprite;
}

void Ship::setPos(int x, int y) {
    _pos = sf::Vector2i(x, y);
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
    int x = getPos().x + _inputX;
    int y = getPos().y + _inputY;
    setPos(x, y);
}

sf::Vector2i Ship::getPos() {
    return _pos;
}

