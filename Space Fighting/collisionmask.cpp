#include "collisionmask.hpp"
#include <cmath>

CollisionMask::CollisionMask() {
    _size = sf::Vector2u(0, 0);
}


CollisionMask::CollisionMask(sf::Image image) {
    std::map<COLOR_NAME, COLLISION_TYPE> typeMap;
    typeMap[BLACK] = SOLID_COLLISION;
    _initWithImage(image, typeMap);
}

CollisionMask::CollisionMask(sf::Image image, std::map<COLOR_NAME, COLLISION_TYPE> colorTypeMap) {
    _initWithImage(image, colorTypeMap);
}
    
void CollisionMask::_initWithImage(sf::Image image, std::map<COLOR_NAME, COLLISION_TYPE> colorTypeMap) {
    int width = image.getSize().x;
    int height = image.getSize().y;
    _size = sf::Vector2u(width, height);
    int pixelCount = width * height;
    _data = std::vector<COLLISION_TYPE>(pixelCount);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            COLLISION_TYPE collisionType;
            COLOR_NAME colName = ColorNames::getNameFromColor(image.getPixel(x,y));
            if (colorTypeMap.count(colName)) {
                collisionType = colorTypeMap[colName];
            }
            
            else {
                collisionType = NO_COLLISION;
            }
            int index = y * width + x;
            _data[index] = collisionType;
        }
    }
    
    int solidCount = 0;
    for (int i = 0; i < pixelCount; i++) {
        if (_data[i] == SOLID_COLLISION) {
            solidCount += 1;
        }
    }
}

sf::Vector2u CollisionMask::getSize() {
    return _size;
}

int CollisionMask::count(int types) {
    int count = 0;
    for (int y = 0; y < _size.y; y++) {
        for (int x = 0; x < _size.x; x++) {
            COLLISION_TYPE ourType = getPixel(x, y);
            if (ourType & types) {
                count += 1;
            }
        }
    }
    return count;
}

COLLISION_TYPE CollisionMask::getPixel(int x, int y) {
    if (x < 0 || y < 0 || x >= _size.x || y >= _size.y) {
        throw("Out of range");
    }
    return _data[y * _size.x + x];
}

std::vector<sf::Vector2u> CollisionMask::getCollisions(CollisionMask &other, sf::Vector2i thisPos, sf::Vector2i otherPos, int ourTypes, int otherTypes) {
    // Find the size of the bounding box overlaps
    sf::Vector2i offset = otherPos - thisPos;
    sf::Vector2u otherSize = other.getSize();
    sf::Rect<int> ourRect = sf::Rect<int>(0, 0, _size.x, _size.y);
    sf::Rect<int> otherRect = sf::Rect<int>(0, 0, otherSize.x, otherSize.y);
    
    int xStart = std::max(ourRect.left, otherRect.left + offset.x);
    int yStart = std::max(ourRect.top, otherRect.top + offset.y);
    int xEnd = std::min(ourRect.left + ourRect.width, otherRect.left + otherRect.width + offset.x);
    int yEnd = std::min(ourRect.top + ourRect.height, otherRect.top + otherRect.height + offset.y);
    
    if (xStart >= xEnd || yStart >= yEnd){
        return std::vector<sf::Vector2u>();
    }
    
    std::vector<sf::Vector2u> collisions = std::vector<sf::Vector2u>();
    for (int ourY = yStart; ourY < yEnd; ourY++) {
        for (int ourX = xStart; ourX < xEnd; ourX++) {
            COLLISION_TYPE ourType = getPixel(ourX, ourY);

            if (! (ourType & ourTypes)) {
                continue;
            }

            int otherX = ourX - offset.x;
            int otherY = ourY - offset.y;
            COLLISION_TYPE otherType = other.getPixel(otherX, otherY);
            if (! (otherType & otherTypes)) {
                continue;
            }
            sf::Vector2u collision = sf::Vector2u(ourX, ourY);
            collisions.push_back(collision);
        }
    }
    return collisions;
}
