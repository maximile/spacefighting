#ifndef imageprocess_hpp
#define imageprocess_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <color.hpp>

class ImageProcess {
public:
    static sf::Image toReferenceColors(sf::Image image);
    static sf::Image convert(sf::Image original, std::map<COLOR_NAME, sf::Color> mapping);
    static sf::Image convert(sf::Image original, std::map<COLOR_NAME, COLOR_NAME> mapping);
};

#endif /* imageprocess_hpp */
