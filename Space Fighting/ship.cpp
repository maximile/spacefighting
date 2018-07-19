#include "ship.hpp"
#include "imageprocess.hpp"
#include "color.hpp"
#include <iostream>

Ship::Ship() {
}

Ship::Ship(sf::Image image) {
    sf::Image processedImage = ImageProcess::toReferenceColors(image);
    _texture.loadFromImage(processedImage);
    _sprite = sf::Sprite(_texture);
    _collisionMask = CollisionMask(image);
    
//    _LABColor test2(sf::Color(173, 35, 35, 255));
//    std::cout << test2.getString();
//    printf("RED %s\n", test2.getString());
    
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
    _vel.x = _vel.x + (_inputX * 0.03);
    _vel.y = _vel.y + (_inputY * 0.05);
    _vel.y = _vel.y + 0.01;

    float x = getPos().x + _vel.x;
    float y = getPos().y + _vel.y;
    setPos(x, y);
}

sf::Vector2f Ship::getPos() {
    return _pos;
}

