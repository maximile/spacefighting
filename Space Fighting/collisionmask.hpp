#ifndef collisionmask_hpp
#define collisionmask_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <color.hpp>

enum {
    NO_COLLISION = 0b1,
    SOLID_COLLISION = 0b10,
    AVAILABLE_COLLISION = 0b100
};
typedef int COLLISION_TYPE;


class CollisionMask {
public:
    CollisionMask();
    CollisionMask(sf::Image image);
    CollisionMask(sf::Image image, std::map<COLOR_NAME, COLLISION_TYPE> colorTypeMap);
    std::vector<sf::Vector2u> getCollisions(CollisionMask &other, sf::Vector2i thisPos, sf::Vector2i otherPos, int ourTypes=SOLID_COLLISION, int otherTypes=SOLID_COLLISION);
    int count(int types);
    sf::Vector2u getSize();
    COLLISION_TYPE getPixel(int x, int y);
private:
    sf::Vector2u _size;
    std::vector<COLLISION_TYPE> _data;
    void _initWithImage(sf::Image image, std::map<COLOR_NAME, COLLISION_TYPE> colorTypeMap);
};


#endif
