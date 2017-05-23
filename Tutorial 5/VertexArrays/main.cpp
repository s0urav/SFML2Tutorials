#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <iostream>

int main()
{
    sf::Vector2i screenDimensions(800, 600);
    sf::Vector2i blockDimensions(10, 10);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "My first SFML game", sf::Style::Default);
    window.setPosition(sf::Vector2i(100, 100));
    //window.setKeyRepeatEnabled(false);
    sf::RectangleShape rect(sf::Vector2f(10, 10));
    rect.setPosition(0, 0);
    rect.setFillColor(sf::Color::Black);
    srand(time(0));
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }
        for(int i = 0; i < screenDimensions.x / blockDimensions.x; ++i)
        {
            for(int j = 0; j < screenDimensions.y / blockDimensions.y; ++j)
            {
                sf::VertexArray vArray(sf::PrimitiveType::Quads, 4);
                vArray[0].position = sf::Vector2f(i * blockDimensions.x, j * blockDimensions.y);
                vArray[1].position = sf::Vector2f(i * blockDimensions.x + blockDimensions.x, j * blockDimensions.y);
                vArray[2].position = sf::Vector2f(i * blockDimensions.x + blockDimensions.x, j * blockDimensions.y + blockDimensions.y);
                vArray[3].position = sf::Vector2f(i * blockDimensions.x, j * blockDimensions.y + blockDimensions.y);
                for(int k = 0; k < 4; ++k)
                {
                    int red = rand() % 255;
                    int green = rand() % 255;
                    int blue = rand() % 255;
                    vArray[k].color = sf::Color(red, green, blue);
                }
                window.draw(vArray);
            }

        }
        window.draw(rect);
        window.display();
        window.clear();
    }
    return 0;
}
