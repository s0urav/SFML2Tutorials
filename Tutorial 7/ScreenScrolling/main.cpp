#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <iostream>

int main()
{
    sf::Vector2i screenDimensions(800, 600);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "My first SFML game", sf::Style::Default);
    window.setPosition(sf::Vector2i(100, 100));

    sf::Texture bTexture;
    if(!bTexture.loadFromFile("background.png"))
    {
        std::cout << "Could not load the background image!" << std::endl;
    }

    sf::Sprite bSprite;
    bSprite.setTexture(bTexture);
    //bSprite.setScale((float)screenDimensions.x / bTexture.getSize().x, (float)screenDimensions.y / bTexture.getSize().y);

    sf::RectangleShape rect(sf::Vector2f(20, 20));
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(0, 0);
    //rect.setOutlineThickness(3);

    sf::Clock clock;
    float moveSpeed = 10000.0f;

    sf::View view;
    view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
    view.setViewport(sf::FloatRect(0, 0, 0.5f, 1.0f));

    //sf::Vector2f position(0, 0); // Первый метод скроллинга
    sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);
    while(window.isOpen())
    {
        clock.restart();
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed :
                    window.close();
                    break;
                case sf::Event::KeyPressed :
                    if(event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Q)
                        window.close();
                    break;
                default:
                    break;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            rect.move(-moveSpeed * clock.getElapsedTime().asSeconds(), 0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            rect.move(moveSpeed * clock.getElapsedTime().asSeconds(), 0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            rect.move(0, -moveSpeed * clock.getElapsedTime().asSeconds());
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            rect.move(0, moveSpeed * clock.getElapsedTime().asSeconds());
        }
        //Первый метод скроллинга
        /*
        position.x = rect.getPosition().x + 10 - screenDimensions.x / 2;
        position.y = rect.getPosition().y + 10 - screenDimensions.y / 2;
        if(position.x < 0) position.x = 0;
        if(position.y < 0) position.y = 0;
        view.reset(sf::FloatRect(position.x, position.y, screenDimensions.x, screenDimensions.y));
        */
        //Второй метод скроллинга
        if(rect.getPosition().x + 10 > screenDimensions.x / 2)
            position.x = rect.getPosition().x + 10;
        else
            position.x = screenDimensions.x / 2;
        if(rect.getPosition().y + 10 > screenDimensions.y / 2)
            position.y = rect.getPosition().y + 10;
        else
            position.y = screenDimensions.y / 2;
        view.setCenter(position);
        window.setView(view);
        //window.setView(window.getDefaultView());
        window.draw(bSprite);
        window.draw(rect);
        window.display();
        window.clear();
    }
    return 0;
}
