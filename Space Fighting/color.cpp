#include "color.hpp"
#include <cmath>


COLOR_NAME ColorNames::getNameFromColor(sf::Color color) {
    if (color.a < 127) {
        return TRANSPARENT;
    }
    
    _LABColor labColor = _LABColor(color);
    COLOR_NAME best_color = NO_COLOR;
    float best_diff = 1.0e10;
    std::map<COLOR_NAME, _LABColor> refCols = _getReferenceLABColors();
    for (std::map<COLOR_NAME, _LABColor>::iterator iter = refCols.begin(); iter != refCols.end(); iter++) {
        float diff = iter->second.getDiff(labColor);
        if (diff < best_diff) {
            best_diff = diff;
            best_color = iter->first;
        }
    }
    
    return best_color;
}


sf::Color ColorNames::getColorFromName(COLOR_NAME name) {
    return _getReferenceSFMLColors()[name];
}


std::map<COLOR_NAME, sf::Color> ColorNames::_getReferenceSFMLColors() {
    static std::map<COLOR_NAME, sf::Color> _referenceColors;
    
    if (_referenceColors.size() > 0) {
        return _referenceColors;
    }
    
    _referenceColors[BLACK] = sf::Color(0, 0, 0, 255);
    _referenceColors[WHITE] = sf::Color(255, 255, 255, 255);
    _referenceColors[GRAY] = sf::Color(127, 127, 127, 255);
    _referenceColors[RED] = sf::Color(173, 35, 35, 255);
    _referenceColors[BLUE] = sf::Color(42, 75, 215, 255);
    _referenceColors[GREEN] = sf::Color(29, 185, 20, 255);
    _referenceColors[YELLOW] = sf::Color(255, 238, 51, 255);
    _referenceColors[ORANGE] = sf::Color(255, 146, 51, 255);
    _referenceColors[BROWN] = sf::Color(129, 74, 25, 255);
    _referenceColors[PURPLE] = sf::Color(129, 38, 192, 255);
    _referenceColors[PINK] = sf::Color(255, 205, 243, 255);
    _referenceColors[TRANSPARENT] = sf::Color(255, 255, 255, 0);
    return _referenceColors;
}

std::map<COLOR_NAME, _LABColor> ColorNames::_getReferenceLABColors() {
    static std::map<COLOR_NAME, _LABColor> _referenceColors;
    if (_referenceColors.size() > 0) {
        return _referenceColors;
    }
    
    std::map<COLOR_NAME, sf::Color> sfmlCols = _getReferenceSFMLColors();
    for (std::map<COLOR_NAME, sf::Color>::iterator iter = sfmlCols.begin(); iter != sfmlCols.end(); iter++) {
        if (iter->first == TRANSPARENT) {
            continue;
        }
        _referenceColors[iter->first] = _LABColor(iter->second);
    }
    return _referenceColors;
}


// LAB color conversion things

_LABColor::_LABColor() {
    _l = _a = _b = 0;
}

_LABColor::_LABColor(sf::Color rgbCol) {
    float r = rgbCol.r / 255.0;
    if (r > 0.04045) r = (std::pow(((r + 0.055) / 1.055), 2.4)) * 100.0;
    else r = (r / 12.92) * 100.0;
    float g = rgbCol.g / 255.0;
    if (g > 0.04045) g = (std::pow(((g + 0.055) / 1.055), 2.4)) * 100.0;
    else g = (g / 12.92) * 100.0;
    float b = rgbCol.b / 255.0;
    if (b > 0.04045) b = (std::pow(((b + 0.055) / 1.055), 2.4)) * 100.0;
    else b = (b / 12.92) * 100.0;
    
    float x = (r * 0.4124 + g * 0.3576 + b * 0.1805) / 95.047;
    float y = (r * 0.2126 + g * 0.7152 + b * 0.0722) / 100.0;
    float z = (r * 0.0193 + g * 0.1192 + b * 0.9505) / 108.883;
    
    if (x > 0.008856) x = std::pow(x, 1.0 / 3.0);
    else x = 7.787 * x + 16.0 / 116.0;
    if (y > 0.008856) y = std::pow(y, 1.0 / 3.0);
    else y = 7.787 * y + 16.0 / 116.0;
    if (z > 0.008856) z = std::pow(z, 1.0 / 3.0);
    else z = 7.787 * z + 16.0 / 116.0;
    
    float lf = (116.0 * y) - 16.0;
    float af = 500.0 * (x - y);
    float bf = 200.0 * (y - z);
    
    _l = int(lf * 255);
    _a = int(af * 255);
    _b = int(bf * 255);
}


float _LABColor::getDiff(_LABColor other) {
    float diff = 0.0;
    diff += (_l - other._l) * (_l - other._l);
    diff += (_a - other._a) * (_a - other._a);
    diff += (_b - other._b) * (_b - other._b);
    return diff;
}


std::string _LABColor::getString() {
    std::string str("LAB ");
    str += std::to_string(_l);
    str += " ";
    str += std::to_string(_a);
    str += " ";
    str += std::to_string(_b);
    return str;
}
