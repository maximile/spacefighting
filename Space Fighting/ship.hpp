#ifndef ship_hpp
#define ship_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "collisionmask.hpp"

enum {
    LANDING_POINT_COLLISION = AVAILABLE_COLLISION
} SHIP_COLLISION_TYPE;

class Ship {
public:
    Ship();
    Ship(sf::Image image);
    CollisionMask getCollisionMask();
    sf::Sprite getSprite();
    sf::Vector2f getPos();
    void land();
    void setPos(float x, float y);
    void applyInputDirection(int x, int y);
    void releaseInputDirection(int x, int y);
    void step(int delta);
    int getRequiredLandingCollisionCount();
private:
    sf::Vector2f _pos;
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Vector2f _vel;
    
    bool _landed;
    int _vel_x_numerator;
    int _vel_x_denominator;

    CollisionMask _collisionMask;
    
    int _landingPixelCount;
    
    int _inputX;
    int _inputY;
};

#endif /* ship_hpp */
