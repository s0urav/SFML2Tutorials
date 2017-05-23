#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <cctype>
#include <iostream>
#include <fstream>

int main()
{
    sf::Vector2i size(600, 600);
    sf::RenderWindow window(sf::VideoMode(size.x, size.y), "Loading maps", sf::Style::Default);
    window.setPosition(sf::Vector2i(100, 100));
    sf::Texture tileTexture;
    sf::Sprite tiles;
    //Загрузка карты
    std::ifstream openFile("map.txt");
    std::vector<std::vector<sf::Vector2i>> map;
    std::vector<sf::Vector2i> temp;
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
                temp.push_back(sf::Vector2i(-1, -1));
            else
                temp.push_back(sf::Vector2i(x - '0', y - '0'));
            std::cout << "temp.size() = " << temp.size() << std::endl;
            if(openFile.peek() == '\n')
            {
                std::cout << "Закидаем строку в матрицу" <<std::endl;
                map.push_back(temp);
                temp.clear();
            }
        }
        map.push_back(temp);
    }
    ////////////
    std::cout << "Печатаем нашу карту" << std::endl;
    for(int i = 0; i < int(map.size()); ++i)
    {
        for(int j = 0; j < int(map[i].size()); ++j)
        {
            std::cout << "(" << map[i][j].x << "," << map[i][j].y << ") ";
        }
        std::cout << std::endl;
    }
    std::cout << "map.size() = " << map.size() << std::endl;
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
        window.clear(sf::Color(0, 200, 230));
        for(int i = 0; i < int(map.size()); ++i)
        {
            for(int j = 0; j < int(map[i].size()); ++j)
            {
                if(map[i][j].x != -1 && map[i][j].y != -1)
                {
                    tiles.setPosition(j * 32, i * 32);
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
