#include "color.hpp"
#include <cmath>


COLOR_NAME ColorNames::getNameFromColor(sf::Color color) {
    if (color.a < 127) {
        return TRANSPARENT;
    }
    
    hsvValues inHsv = ColorNames::colorToHsvValues(color);
    COLOR_NAME bestColor = NO_COLOR;
    float bestDiff = 1.0e10;
    std::map<COLOR_NAME, hsvValues> refVals = _getReferenceHsvValues();
    for (std::map<COLOR_NAME, hsvValues>::iterator iter = refVals.begin(); iter != refVals.end(); iter++) {
        COLOR_NAME refName = iter->first;
        hsvValues refHsv = iter->second;
        float diff = 0.0;
        diff += abs(refHsv.h - inHsv.h);
        diff += abs(refHsv.s - inHsv.s);
        diff += abs(refHsv.v - inHsv.v);
        if (diff < bestDiff) {
            bestDiff = diff;
            bestColor = refName;
        }
    }
    return bestColor;
}


sf::Color ColorNames::getColorFromName(COLOR_NAME name) {
    return getReferenceColors()[name];
}


std::map<COLOR_NAME, sf::Color> ColorNames::getReferenceColors() {
    static std::map<COLOR_NAME, sf::Color> _referenceColors;
    
    if (_referenceColors.size() > 0) {
        return _referenceColors;
    }
    
    _referenceColors[BLACK] = sf::Color(0, 0, 0, 255);
    _referenceColors[WHITE] = sf::Color(255, 255, 255, 255);
    _referenceColors[GRAY] = sf::Color(127, 127, 127, 255);
    _referenceColors[RED] = sf::Color(255, 0, 0, 255);
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


std::map<COLOR_NAME, hsvValues> ColorNames::_getReferenceHsvValues() {
    static std::map<COLOR_NAME, hsvValues> _referenceValues;
    if (_referenceValues.size() > 0) {
        return _referenceValues;
    }
    
    std::map<COLOR_NAME, sf::Color> sfmlCols = getReferenceColors();
    for (std::map<COLOR_NAME, sf::Color>::iterator iter = sfmlCols.begin(); iter != sfmlCols.end(); iter++) {
        if (iter->first == TRANSPARENT) {
            continue;
        }
        _referenceValues[iter->first] = ColorNames::colorToHsvValues(iter->second);
    }
    return _referenceValues;
}

hsvValues ColorNames::colorToHsvValues(sf::Color inCol) {
    hsvValues outVals;
    float inR = inCol.r / 255.0;
    float inG = inCol.g / 255.0;
    float inB = inCol.b / 255.0;

    // Value from rgb max
    float minRgb, maxRgb;
    minRgb = inR < inG ? inR : inG;
    minRgb = minRgb < inB ? minRgb : inB;
    maxRgb = inR > inG ? inR : inG;
    maxRgb = maxRgb > inB ? maxRgb : inB;
    outVals.v = maxRgb;
    
    // Saturation
    float delta = maxRgb - minRgb;
    if (delta < 0.00001)
    {
        outVals.s = 0.0;
        outVals.h = 0.0;
        return outVals;
    }
    outVals.s = (delta / maxRgb);

    // Hue (0.0-6.0)
    if (inR >= maxRgb) {
        outVals.h = (inG - inB) / delta;  // Between yellow & magenta
    }
    else if (inG >= maxRgb) {
        outVals.h = 2.0 + (inB - inR) / delta;  // Between cyan & yellow
    }
    else {
        outVals.h = 4.0 + (inR - inG) / delta;  // Between magenta & cyan
    }
    
    // Scale hue to 0.0-1.0
    outVals.h /= 6.0;
    if (outVals.h < 0.0) {
        outVals.h += 1.0;
    }
    
    return outVals;
}
