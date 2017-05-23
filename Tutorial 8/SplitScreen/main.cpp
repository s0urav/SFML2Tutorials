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
    sf::RectangleShape rect2(sf::Vector2f(20, 20));
    rect2.setFillColor(sf::Color::Blue);
    rect2.setPosition(screenDimensions.x / 2, 0);
    //rect.setOutlineThickness(3);

    sf::Clock clock;
    float moveSpeed = 10000.0f;

    sf::View view1, view2;
    //view1.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
    view1.setViewport(sf::FloatRect(0, 0, 0.5f, 1.0f));
    view1.setSize(screenDimensions.x / 2, screenDimensions.y);
    view2.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1.0f));
    view2.setSize(screenDimensions.x / 2, screenDimensions.y);
    //sf::Vector2f position(0, 0); // Первый метод скроллинга
    sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);
    sf::Vector2f position2(position);
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
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            rect2.move(-moveSpeed * clock.getElapsedTime().asSeconds(), 0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            rect2.move(moveSpeed * clock.getElapsedTime().asSeconds(), 0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            rect2.move(0, -moveSpeed * clock.getElapsedTime().asSeconds());
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            rect2.move(0, moveSpeed * clock.getElapsedTime().asSeconds());
        }
        //Зумминг видовых портов)
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
        {
            view1.zoom(1.001f);
            view2.zoom(1.001f);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
        {
            view1.zoom(0.999f);
            view2.zoom(0.999f);
        }
        //Вращение видовых портов
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            view1.rotate(+0.1f);
            view2.rotate(+0.1f);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            view1.rotate(-0.1f);
            view2.rotate(-0.1f);
        }
        if(rect.getPosition().x + 10 > view1.getSize().x / 2)
            position.x = rect.getPosition().x + 10;
        else
            position.x = view1.getSize().x / 2;
        if(rect.getPosition().y + 10 > view1.getSize().y / 2)
            position.y = rect.getPosition().y + 10;
        else
            position.y = view1.getSize().y / 2;

        view1.setCenter(position);

        if(rect2.getPosition().x + 10 > view2.getSize().x / 2)
            position2.x = rect2.getPosition().x + 10;
        else
            position2.x = view2.getSize().x / 2;
        if(rect2.getPosition().y + 10 > view2.getSize().y / 2)
            position2.y = rect2.getPosition().y + 10;
        else
            position2.y = view2.getSize().y / 2;

        view2.setCenter(position2);

        window.setView(view1);
        window.draw(bSprite);
        window.draw(rect);
        window.draw(rect2);

        window.setView(view2);
        window.draw(bSprite);
        window.draw(rect2);
        window.draw(rect);

        window.display();
        window.clear();
      }
    return 0;
}
