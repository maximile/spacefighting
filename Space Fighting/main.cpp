#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "screen.hpp"
#include "ship.hpp"

class Level {
    
};

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Space Fighting");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Image bg;
    bg.loadFromFile(resourcePath() + "cool.png");
    
    Screen screen(bg);
//    screen.loadFromFile(resourcePath() + "cool.png");
//
//    sf::Vector2u bgsize = bg.getSize();
//    for (int y = 0; y < bgsize.y; y++) {
//        for (int x = 0; x < bgsize.x; x++) {
//            sf::Color col = bg.getPixel(x, y);
//            if (col.r < 127) {
//                col = sf::Color(200, 100, 100);
//            }
//            else {
//                col = sf::Color(100, 200, 200);
//            }
//            bg.setPixel(x, y, col);
//        }
//    }

    sf::Image shipImage;
    shipImage.loadFromFile(resourcePath() + "car.png");
    Ship ship(shipImage);
    
    sf::Texture collisionTexture;
    collisionTexture.loadFromFile(resourcePath() + "icon.png");
    sf::Sprite collisionSprite = sf::Sprite(collisionTexture);
    collisionSprite.setScale(0.5, 0.5);
    collisionSprite.setPosition(100, 500);

    sf::Texture testTexture;
    testTexture.loadFromFile(resourcePath() + "blue.png");
    std::vector<sf::Sprite> testSprites = std::vector<sf::Sprite>();
    for (int i = 0; i < 500; i++) {
        sf::Sprite testSprite = sf::Sprite(testTexture);
        testSprites.push_back(testSprite);
    }
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                if (event.key.code == sf::Keyboard::Left) {
                    ship.applyInputDirection(-1, 0);
                }
                if (event.key.code == sf::Keyboard::Right) {
                    ship.applyInputDirection(1, 0);
                }
                if (event.key.code == sf::Keyboard::Up) {
                    ship.applyInputDirection(0, -1);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    ship.applyInputDirection(0, 1);
                }
            }
            
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Left) {
                    ship.releaseInputDirection(-1, 0);
                }
                if (event.key.code == sf::Keyboard::Right) {
                    ship.releaseInputDirection(1, 0);
                }
                if (event.key.code == sf::Keyboard::Up) {
                    ship.releaseInputDirection(0, -1);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    ship.releaseInputDirection(0, 1);
                }
            }
        }

        ship.step(0.05);
        
        // Clear screen
        window.clear();

        sf::RenderTexture canvasTexture;
        sf::Vector2u windowSize = window.getSize();
        assert(windowSize.x % 2 == 0);
        assert(windowSize.y % 2 == 0);
        canvasTexture.create(window.getSize().x / 2, window.getSize().y / 2);
        canvasTexture.setSmooth(false);
        
        // Draw the sprite
        canvasTexture.draw(screen.getBackgroundSprite());
        canvasTexture.draw(ship.getSprite());

        // Test for collision
        CollisionMask bgMask = screen.getCollisionMask();
        CollisionMask shipMask = ship.getCollisionMask();
        std::vector<sf::Vector2u> collisions = bgMask.getCollisions(shipMask, sf::Vector2i(), sf::Vector2i(ship.getPos()));
        
        if (collisions.size() > 0) {
            canvasTexture.draw(collisionSprite);
            for (int tsi = 0; tsi < testSprites.size(); tsi++) {
                sf::Sprite testSprite = testSprites[tsi];
                int colli = int(random() % (collisions.size()));
                testSprite.setPosition(collisions[colli].x, collisions[colli].y);
                canvasTexture.draw(testSprite);
            }
        }
        
        canvasTexture.display();
        sf::Sprite canvasSprite = sf::Sprite(canvasTexture.getTexture());
        canvasSprite.setScale(2.0, 2.0);
        window.draw(canvasSprite);
        window.display();
    }

    return EXIT_SUCCESS;
}

