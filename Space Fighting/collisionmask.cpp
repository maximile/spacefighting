#include "collisionmask.hpp"
#include <cmath>

CollisionMask::CollisionMask() {
    _size = sf::Vector2u(0, 0);
}

CollisionMask::CollisionMask(sf::Image image) {
    int width = image.getSize().x;
    int height = image.getSize().y;
    _size = sf::Vector2u(width, height);
    int pixelCount = width * height;
    _data = std::vector<COLLISION_TYPE>(pixelCount);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            sf::Color sourceColor = image.getPixel(x, y);
            COLLISION_TYPE collisionType;
            if (sourceColor.r <= 127 && sourceColor.a > 127) {
                collisionType = SOLID_COLLISION;
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

COLLISION_TYPE CollisionMask::getPixel(int x, int y) {
    if (x < 0 || y < 0 || x >= _size.x || y >= _size.y) {
        throw("Out of range");
    }
    return _data[y * _size.x + x];
}

std::vector<sf::Vector2u> CollisionMask::getCollisions(CollisionMask &other, sf::Vector2i thisPos, sf::Vector2i otherPos) {
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

            if (ourType != SOLID_COLLISION) {
                continue;
            }

            int otherX = ourX - offset.x;
            int otherY = ourY - offset.y;
            COLLISION_TYPE otherType = other.getPixel(otherX, otherY);
            if (otherType != SOLID_COLLISION) {
                continue;
            }
            sf::Vector2u collision = sf::Vector2u(ourX, ourY);
            collisions.push_back(collision);
        }
    }
    return collisions;
}


//float _LABColor::getDiff(_LABColor other) {
//    float diff = 0.0;
//    diff += abs(l - other.l);
//    diff += abs(a - other.a);
//    diff += abs(b - other.b);
//    return diff;
//}

//COLOR_NAME CollisionMask::getColorName(sf::Color color) {
//    if (color.a < 127) {
//        return TRANSPARENT;
//    }
//
//    _LABColor labColor = _LABColor(color);
//    COLOR_NAME best_color = NO_COLOR;
//    float best_diff = 1.0e10;
//    std::map<COLOR_NAME, _LABColor> refCols = _getReferenceColors();
//    for (std::map<COLOR_NAME, _LABColor>::iterator iter = refCols.begin(); iter != refCols.end(); iter++) {
//        float diff = iter->second.getDiff(labColor);
//        if (diff < best_diff) {
//            best_diff = diff;
//            best_color = iter->first;
//        }
//    }
//
//    return best_color;
//}
//

//_LABColor::_LABColor() {
//    l = a = b = 0;
//}
//
//
//_LABColor::_LABColor(float l_val, float a_val, float b_val) {
//    l = l_val;
//    a = a_val;
//    b = b_val;
//}
//
//
//_LABColor::_LABColor(sf::Color rgbCol) {
//    float r = rgbCol.r / 255.0;
//    if (r > 0.4045) r = (std::pow(((r + 0.055) / 1.055), 2.4)) * 100.0;
//    else r = (r / 12.92) * 100.0;
//    float g = rgbCol.g / 255.0;
//    if (g > 0.4045) g = (std::pow(((g + 0.055) / 1.055), 2.4)) * 100.0;
//    else g = (g / 12.92) * 100.0;
//    float b = rgbCol.b / 255.0;
//    if (b > 0.4045) b = (std::pow(((b + 0.055) / 1.055), 2.4)) * 100.0;
//    else b = (b / 12.92) * 100.0;
//
//    float x = (r * 0.4124 + g * 0.3576 + b * 0.1805) / 95.047;
//    float y = (r * 0.2126 + g * 0.7152 + b * 0.0722) / 100.0;
//    float z = (r * 0.0193 + g * 0.1192 + b * 0.9505) / 108.883;
//
//    if (x > 0.008856) x = std::pow(x, 1.0 / 3.0);
//    else x = 7.787 * x + 16.0 / 116.0;
//    if (y > 0.008856) y = std::pow(y, 1.0 / 3.0);
//    else y = 7.787 * y + 16.0 / 116.0;
//    if (z > 0.008856) z = std::pow(z, 1.0 / 3.0);
//    else z = 7.787 * z + 16.0 / 116.0;
//
//    float lf = (116.0 * y) - 16.0;
//    float af = 500.0 * (x - y);
//    float bf = 200.0 * (y - z);
//
//    l = int(lf * 255);
//    a = int(af * 255);
//    b = int(bf * 255);

//                for v in xyz:
//                    if v > 0.008856:
//                        v = v ** (1.0 / 3.0)
//                        else:
//                            v = 7.787 * v + 16.0 / 116.0
//                            new_xyz.append(v)
//                            x, y, z = new_xyz
//                            l = (116.0 * y) - 16.0
//                            a = 500.0 * (x - y)
//                            b = 200 * (y - z)
//                            return l, a, b

//}

//    for (int i = 0; i < LAB_COLORS.size(); i++) {
//
//        float diff = labColor.getDiff(LAB_COLORS[i]);
//    }
//
//    float min_diff = 1.0e10;
//
//    min_diff = sys.float_info.max
//    for col, lab2 in LAB_FOR_COLORS.items():
//    diff = 0.0
//    for c1, c2 in zip(lab, lab2):
//    diff += (c1 - c2) * (c1 - c2)
//    if diff < min_diff:
//    min_diff = diff
//    min_diff_col = col
//    _col_cache[cache_key] = min_diff_col
//    return min_diff_col
//        }
//
