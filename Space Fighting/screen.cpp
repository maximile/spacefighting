#include "screen.hpp"


Screen::Screen(sf::Image image) {
    _source = image;
    _bg_texture.loadFromImage(image);
    _bg_sprite = sf::Sprite(_bg_texture);
    _collision_mask = CollisionMask(image);
}

sf::Sprite Screen::getBackgroundSprite() {
    return _bg_sprite;
}

CollisionMask Screen::getCollisionMask() {
    return _collision_mask;
}
