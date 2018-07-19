#ifndef color_hpp
#define color_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

enum COLOR_NAME {
    NO_COLOR = -1,
    TRANSPARENT = 0,
    BLACK,
    WHITE,
    GRAY,
    RED,
    BLUE,
    GREEN,
    YELLOW,
    ORANGE,
    BROWN,
    PURPLE,
    PINK
};


class _LABColor {
public:
    _LABColor();
    _LABColor(sf::Color rgbcol);
//    _LABColor(float l, float a_val, float b_val);
    float getDiff(_LABColor other);
    std::string getString();
private:
    sf::Uint8 _l, _a, _b;
};


class ColorNames {
public:
    static COLOR_NAME getNameFromColor(sf::Color color);
    static sf::Color getColorFromName(COLOR_NAME name);
private:
    static std::map<COLOR_NAME, sf::Color> _getReferenceSFMLColors();
    static std::map<COLOR_NAME, _LABColor> _getReferenceLABColors();
};


#endif /* color_hpp */
