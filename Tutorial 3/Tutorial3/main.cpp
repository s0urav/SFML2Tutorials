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
    enum Direction {DOWN, LEFT, RIGHT, UP};
    //int sourceX = 32, sourceY = DOWN;
    float frameCounter = 0, frameSpeed = 500, frameSwitch = 100;
    sf::Clock clock;
    bool updateFrame = true;
    sf::Vector2i source(0, DOWN);
    sf::Vector2i pSize(51, 55);
    sf::Texture pTexture;
    sf::Sprite pSprite;

    if(!pTexture.loadFromFile("SpriteSheet.png"))
    {
        std::cout << "Could not load image" << std::endl;
    }
    //pSprite.setRotation(90);
    pSprite.setTexture(pTexture);
    pSprite.setPosition(50, 140);
    //std::cout << "width = " << pTexture.getSize().x << std::endl;
    //std::cout << "height = " << pTexture.getSize().y << std::endl;
    /*srand(time(NULL));
    int delay = 30;
    int counter = 0;
    float angle = 0.0f;*/
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
        //Обработка нажатий клавиш вне цикла обработки очереди событий
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            source.y = UP;
            pSprite.move(0, -1);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            source.y = DOWN;
            pSprite.move(0, 1);
         }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            source.y = LEFT;
            pSprite.move(-1, 0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            source.y = RIGHT;
            pSprite.move(1, 0);
        }
        //Обработка нажатий клавиш мыши вне очереди обработки событий
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f playerPosition = pSprite.getPosition();
        //std::cout << "Mouse postion - X: " << mousePosition.x << " Y: " << mousePosition.y << std::endl;
        //Включаем анимацию персонажа ЛКМ и отключаем ее ПКМ
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            updateFrame = true;
        }
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            updateFrame = false;
        }
        //Передвижение персонажа с помощью мышки
        if(mousePosition.x < playerPosition.x + 25)
        {
            source.y = LEFT;
            pSprite.move(-1, 0);
        }
        else if(mousePosition.x > playerPosition.x + pSize.x - 25)
        {
            source.y = RIGHT;
            pSprite.move(1, 0);
        }
        else if(mousePosition.y < playerPosition.y)
        {
            source.y = UP;
            pSprite.move(0, -1);
        }
        else if(mousePosition.y > playerPosition.y + pSize.y)
        {
            source.y = DOWN;
            pSprite.move(0, 1);
        }
        std::cout << "player position x = " << playerPosition.x << " y = " << playerPosition.y << std::endl;
        std::cout << "mouse position x = " << mousePosition.x << " y = " << mousePosition.y << std::endl;
        //Для одинаковой скорости анимации персонажа на компьютерах разной мощности
        //Ноутбук выполняет игровой цикл каждые 16 милисекунд
        frameCounter = updateFrame ? frameCounter + frameSpeed * clock.restart().asSeconds() : 0;
        if(frameCounter >= frameSwitch)
        {
            source.x += 1;
            if(source.x == 3)
                source.x = 0;
            frameCounter = 0;
        }
        /*if(++counter >= delay)
        {
            int randX = rand() % (WINDOW_WIDTH - 40);
            int randY = rand() % (WINDOW_HEIGHT - 40);
            pSprite.setPosition(randX, randY);
            counter = 0;
            angle += 90;
            if(angle == 360)
                angle = 0;
            pSprite.setRotation(angle);
        }*/
        pSprite.setTextureRect(sf::IntRect(source.x * pSize.x, source.y * pSize.y, pSize.x, pSize.y));
        window.clear();
        window.draw(pSprite);
        window.display();
    }
    return 0;
}
