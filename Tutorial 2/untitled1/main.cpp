#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <ctime>
#include <stdlib.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My first SFML game", sf::Style::Default);
    sf::Vector2u size(400, 400);
    window.setSize(size);
    window.setTitle("New title");
    window.setPosition(sf::Vector2i(100, 100));
    sf::Texture pTexture;
    sf::Sprite pSprite;
    if(!pTexture.loadFromFile("tank.png", sf::IntRect(30, 0, 30, 30)))
    {
        std::cout << "Could not load image" << std::endl;
    }
    pSprite.setRotation(90);
    pSprite.setTexture(pTexture);
    pSprite.setPosition(50, 140);
    srand(time(NULL));
    int delay = 30;
    int counter = 0;
    float angle = 0.0f;
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Q)
                    window.close();
            }
        }
        if(++counter >= delay)
        {
            int randX = rand() % (WINDOW_WIDTH - 40);
            int randY = rand() % (WINDOW_HEIGHT - 40);
            pSprite.setPosition(randX, randY);
            counter = 0;
            angle += 90;
            if(angle == 360)
                angle = 0;
            pSprite.setRotation(angle);
        }
        window.clear();
        window.draw(pSprite);
        window.display();
    }
    return 0;
}
