#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <ctime>
#include <stdlib.h>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gravity", sf::Style::Default);
    window.setPosition(sf::Vector2i(100, 100));
    const float gravity = 1.0f;
    float moveSpeed = 5.0f;
    float jumpSpeed = 20.0f;
    const float bottom = WINDOW_HEIGHT - 64;
    sf::Vector2f velocity(0, 0);
    sf::CircleShape circle;
    sf::RectangleShape grass;
    grass.setFillColor(sf::Color::Green);
    grass.setSize(sf::Vector2f(WINDOW_WIDTH, 32));
    grass.setPosition(0, bottom + 32);
    circle.setPosition(10, bottom);
    circle.setRadius(16);
    circle.setFillColor(sf::Color::Magenta);
    bool isInAir = false;
    int counter = 0;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed :
                    window.close();
                    break;
                case sf::Event::KeyPressed :
                    if(event.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;
                default :
                    break;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            velocity.x = -moveSpeed;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            velocity.x = +moveSpeed;
        }
        else if(!isInAir)
            velocity.x = 0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isInAir)
        {
            velocity.y = -jumpSpeed;
            circle.move(velocity.x, velocity.y);
            isInAir = true;
        }
        if(isInAir)
        {
            velocity.y += gravity;
            isInAir = circle.getPosition().y + 2 * circle.getRadius() < bottom;
        }
        else
        {
            circle.setPosition(circle.getPosition().x, bottom);
            velocity.y = 0;
        }
        circle.move(velocity.x, velocity.y);
        window.clear(sf::Color(0, 200, 180));
        window.draw(grass);
        window.draw(circle);
        window.display();
    }
    return 0;
}
