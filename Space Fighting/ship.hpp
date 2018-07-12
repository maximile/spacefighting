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
    sf::Vector2f getPos();
    void setPos(float x, float y);
    void applyInputDirection(int x, int y);
    void releaseInputDirection(int x, int y);
    void step(int delta);
private:
    sf::Vector2f _pos;
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Vector2f _vel;
    
    int _vel_x_numerator;
    int _vel_x_denominator;

    CollisionMask _collisionMask;
    
    int _inputX;
    int _inputY;
};

#endif /* ship_hpp */
