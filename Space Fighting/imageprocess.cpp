#include "imageprocess.hpp"
#include "color.hpp"

sf::Image ImageProcess::toReferenceColors(sf::Image original) {
    sf::Image processed;
    processed.create(original.getSize().x, original.getSize().y);
    for (int y = 0; y < original.getSize().y; y++) {
        for (int x = 0; x < original.getSize().x; x++) {
            sf::Color originalCol = original.getPixel(x, y);
            COLOR_NAME name = ColorNames::getNameFromColor(originalCol);
            sf::Color processedCol = ColorNames::getColorFromName(name);
            processed.setPixel(x, y, processedCol);
        }
    }
    return processed;
}
