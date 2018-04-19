#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <ctime>
#include <stdlib.h>

constexpr unsigned int WINDOW_WIDTH {600}, WINDOW_HEIGHT {600};

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "My first SFML game", sf::Style::Default);

    sf::Vector2u size(400, 400);

    window.setSize(size);

    window.setTitle("New title");

    window.setPosition(sf::Vector2i(100, 100));

    sf::Texture pTexture;

    sf::Sprite pSprite;

    constexpr unsigned int sprite_width {60}, sprite_height{60};

    if(!pTexture.loadFromFile("tank.png", sf::IntRect(0, 0, sprite_width, sprite_height)))
    {
        std::cerr << "Could not load image" << std::endl;
    }

    pSprite.setTexture(pTexture);

    pSprite.setOrigin(sprite_width/2, sprite_height/2);

    pSprite.setPosition(50, 140);


    srand(time(NULL));

    constexpr int delay = 3000;
    int counter = 0;
    int angle {0}; 

    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            switch (event.type)
            {
            case(sf::Event::Closed):
                window.close();
                break;

            case(sf::Event::KeyPressed):

                if(event.key.code == sf::Keyboard::Q)
                {
                    window.close();
                }
                break;
            }
        }

        if(++counter >= delay)
        {
            const int randX = rand() % (WINDOW_WIDTH - 40);
            const int randY = rand() % (WINDOW_HEIGHT - 40);

            pSprite.setPosition(randX, randY);

            counter = 0;

            angle += 60;
            angle %= 360;

            pSprite.setRotation(angle);
        }

        window.clear();
        window.draw(pSprite);
        window.display();
    }

    return 0;
}
