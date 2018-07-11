#ifndef ship_hpp
#define ship_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "collisionmask.hpp"

class Ship {
public:
    Ship();
    Ship(sf::Image image);
    CollisionMask getCollisionMask();
    sf::Sprite getSprite();
    sf::Vector2i getPos();
    void setPos(int x, int y);
    void applyInputDirection(int x, int y);
    void releaseInputDirection(int x, int y);
    void step(int delta);
private:
    sf::Vector2i _pos;
    sf::Texture _texture;
    sf::Sprite _sprite;
    CollisionMask _collisionMask;
    
    int _inputX;
    int _inputY;
};

#endif /* ship_hpp */
