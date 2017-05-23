#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <ctime>
#include <stdlib.h>

int main()
{
    sf::Vector2i screenDimensions(800, 600);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "My first SFML game", sf::Style::Default);
    sf::Vector2u size(400, 400);
    window.setSize(size);
    window.setTitle("New title");
    window.setPosition(sf::Vector2i(100, 100));
    sf::RectangleShape rect(sf::Vector2f(200, 100));
    rect.setPosition(100, 100);
    rect.setFillColor(sf::Color::Magenta);
    rect.setOutlineColor(sf::Color(0, 255, 100, 127));
    rect.setOutlineThickness(3);
    rect.setScale(2, 2);
    //rect.setRotation(45);
    sf::Texture pTexture;
    pTexture.loadFromFile("SpriteSheet.png");
    //Можно вставлять текстуру в геометрическую фигуру
    //rect.setTexture(&pTexture);
    sf::CircleShape circle(50, 200);
    circle.setPosition(300, 400);
    circle.setFillColor(sf::Color::Yellow);
     //rect.setOrigin(50, -50);
    sf::ConvexShape myShape(3);
    myShape.setPoint(0, sf::Vector2f(100, 100));
    myShape.setPoint(1, sf::Vector2f(200, 100));
    myShape.setPoint(2, sf::Vector2f(150, 250));
    myShape.setOutlineColor(sf::Color::Red);
    myShape.setOutlineThickness(10);
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
        window.clear();
        window.draw(rect);
        window.draw(circle);
        window.draw(myShape);
        window.display();

    }
    return 0;
}
