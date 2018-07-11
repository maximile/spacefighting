#ifndef screen_hpp
#define screen_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "collisionmask.hpp"

class Screen {
public:
    Screen(sf::Image image);
    sf::Sprite getBackgroundSprite();
    CollisionMask getCollisionMask();
private:
    sf::Image _source;
    sf::Texture _bg_texture;
    sf::Sprite _bg_sprite;
    CollisionMask _collision_mask;
};

#endif
