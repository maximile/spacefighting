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

typedef struct {
    float h, s, v;
} hsvValues;


class ColorNames {
public:
    static COLOR_NAME getNameFromColor(sf::Color color);
    static sf::Color getColorFromName(COLOR_NAME name);
    static std::map<COLOR_NAME, sf::Color> getReferenceColors();
private:
    static std::map<COLOR_NAME, hsvValues> _getReferenceHsvValues();
    static hsvValues colorToHsvValues(sf::Color inCol);
};


#endif /* color_hpp */
