#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <cctype>
#include <iostream>
#include <fstream>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Loading maps", sf::Style::Default);
    window.setPosition(sf::Vector2i(100, 100));
    sf::Texture tileTexture;
    sf::Sprite tiles;
    //Загрузка карты
    std::ifstream openFile("map.txt");
    sf::Vector2i map[100][100];
    sf::Vector2i loadCounter(0, 0);
    if(openFile.is_open())
    {
        std::string tileLocation;
        openFile >> tileLocation;
        if(!tileTexture.loadFromFile(tileLocation))
        {
            std::cout << "Could not load image file" << std::endl;
        }
        tiles.setTexture(tileTexture);
        while(!openFile.eof())
        {
            std::string str;
            openFile >> str;
            char x = str[0];
            char y = str[2];
            if(!isdigit(x) || !isdigit(y))
                map[loadCounter.x][loadCounter.y] = sf::Vector2i(-1, -1);
            else
                map[loadCounter.x][loadCounter.y] = sf::Vector2i(x - '0', y - '0');
            if(openFile.peek() == '\n')
            {
                loadCounter.x = 0;
                loadCounter.y++;
            }
            else
                loadCounter.x++;
        }
        loadCounter.y++;
    }
    ////////////
    std::cout << "Печатаем нашу карту" << std::endl;
    for(int i = 0; i < loadCounter.x; ++i)
    {
        for(int j = 0; j < loadCounter.y; ++j)
        {
            std::cout << "(" << map[j][i].x << "," << map[j][i].y << ") ";
        }
        std::cout << std::endl;
    }
    std::cout << "loadCounter.x = " << loadCounter.x << std::endl;
    std::cout << "loadCounter.y = " << loadCounter.y << std::endl;
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
        window.clear(sf::Color(0, 240, 255));
        for(int i = 0; i < loadCounter.x; ++i)
        {
            for(int j = 0; j < loadCounter.y; ++j)
            {
                if(map[i][j].x != -1 && map[i][j].y != -1)
                {
                    tiles.setPosition(i * 32, j * 32);
                    tiles.setTextureRect(sf::IntRect(map[i][j].x * 32, map[i][j].y * 32, 32, 32));
                    window.draw(tiles);
                }
            }
        }
        window.draw(tiles);
        window.display();
    }
    return 0;
}
