#include "ship.hpp"
#include "imageprocess.hpp"
#include "color.hpp"
#include <iostream>

Ship::Ship() {
}

Ship::Ship(sf::Image image) {
    std::map<COLOR_NAME, COLOR_NAME> colMap;
    colMap[BLACK] = BLACK;
    colMap[GREEN] = BLACK;
    sf::Image processedImage = ImageProcess::convert(image, colMap);
    
//    sf::Image processedImage = ImageProcess::toReferenceColors(image);
    _texture.loadFromImage(processedImage);
    _sprite = sf::Sprite(_texture);
    _landed = false;
    
    std::map<COLOR_NAME, int> colorCollisionMap;
    colorCollisionMap[YELLOW] = LANDING_POINT_COLLISION;
    colorCollisionMap[BLACK] = SOLID_COLLISION;
    colorCollisionMap[GREEN] = SOLID_COLLISION;

    _collisionMask = CollisionMask(image, colorCollisionMap);
    _landingPixelCount = _collisionMask.count(LANDING_POINT_COLLISION);
}

int Ship::getRequiredLandingCollisionCount() {
    return _landingPixelCount;
}


CollisionMask Ship::getCollisionMask() {
    return _collisionMask;
}

sf::Sprite Ship::getSprite() {
    return _sprite;
}

void Ship::land() {
    _vel.x = _vel.y = 0;
    _landed = true;
}

void Ship::setPos(float x, float y) {
    _pos = sf::Vector2f(x, y);
    _sprite.setPosition(x, y);
}

void Ship::applyInputDirection(int x, int y) {
    if (x != 0) _inputX = x;
    if (y != 0) _inputY = y;
    if (y < 0) {
        _landed = false;
        _pos.y -= 1;
    }
}

void Ship::releaseInputDirection(int x, int y) {
    if (x != 0) _inputX = 0;
    if (y != 0) _inputY = 0;
}

void Ship::step(int delta) {
    if (_landed) {
        return;
    }
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

