#include "imageprocess.hpp"
#include "color.hpp"

//sf::Image ImageProcess::toReferenceColors(sf::Image original) {
//    sf::Image processed;
//    processed.create(original.getSize().x, original.getSize().y);
//    for (int y = 0; y < original.getSize().y; y++) {
//        for (int x = 0; x < original.getSize().x; x++) {
//            sf::Color originalCol = original.getPixel(x, y);
//            COLOR_NAME name = ColorNames::getNameFromColor(originalCol);
//            sf::Color processedCol = ColorNames::getColorFromName(name);
//            processed.setPixel(x, y, processedCol);
//        }
//    }
//    return processed;
//}

sf::Image ImageProcess::toReferenceColors(sf::Image original) {
    return convert(original, ColorNames::getReferenceColors());
}


sf::Image ImageProcess::convert(sf::Image original, std::map<COLOR_NAME, COLOR_NAME> mapping) {
    std::map<COLOR_NAME, sf::Color> mapping2;
    std::map<COLOR_NAME, sf::Color> refCols = ColorNames::getReferenceColors();
    for (std::map<COLOR_NAME, COLOR_NAME>::iterator iter = mapping.begin(); iter != mapping.end(); iter++) {
        mapping2[iter->first] = refCols[iter->second];
    }
    return convert(original, mapping2);
}


sf::Image ImageProcess::convert(sf::Image original, std::map<COLOR_NAME, sf::Color> mapping) {
    sf::Image processed;
    processed.create(original.getSize().x, original.getSize().y);
    for (int y = 0; y < original.getSize().y; y++) {
        for (int x = 0; x  < original.getSize().x; x++) {
            sf::Color originalCol = original.getPixel(x, y);
            COLOR_NAME name = ColorNames::getNameFromColor(originalCol);
            sf::Color processedCol;
            if (mapping.count(name)) {
                processedCol = mapping[name];
            }
            else {
                processedCol = sf::Color(255, 255, 255, 0);
            }
            processed.setPixel(x, y, processedCol);
        }
    }
    return processed;
}
