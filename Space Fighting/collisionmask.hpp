#ifndef collisionmask_hpp
#define collisionmask_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

enum COLLISION_TYPE {
    NO_COLLISION,
    SOLID_COLLISION
};

class CollisionMask {
public:
    CollisionMask();
    CollisionMask(sf::Image image);
    std::vector<sf::Vector2u> getCollisions(CollisionMask &other, sf::Vector2i thisPos, sf::Vector2i otherPos);
    sf::Vector2u getSize();
    COLLISION_TYPE getPixel(int x, int y);
private:
    sf::Vector2u _size;
    std::vector<COLLISION_TYPE> _data;
};

#endif
