#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>

typedef std::vector<std::vector<sf::Vector2i>> Map;

void loadMap(const std::string &pathToFile, Map &map, sf::Texture &texture, sf::Sprite &tiles);
void drawMap(const Map &map, sf::Sprite &tiles, sf::RenderWindow &window);
void printMap(const Map &map);

int main()
{
    sf::Vector2i size(600, 600);
    sf::RenderWindow window(sf::VideoMode(size.x, size.y), "Loading maps", sf::Style::Default);
    window.setPosition(sf::Vector2i(100, 100));
    sf::Texture tileTexture;
    sf::Sprite tiles;
    //Загрузка карты
    std::vector<std::vector<sf::Vector2i>> map;
    loadMap("map.txt", map, tileTexture, tiles);
    printMap(map);
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
                    else if(event.key.code == sf::Keyboard::L)
                        loadMap("map.txt", map, tileTexture, tiles);
                    break;
                default :
                    break;
            }
        }
        window.clear(sf::Color(0, 200, 230));
        drawMap(map, tiles, window);
        window.display();
    }
    return 0;
}
void loadMap(const std::string &pathToFile, Map &map, sf::Texture &texture, sf::Sprite &tiles)
{
    if(!map.empty())
        map.clear();
    std::ifstream openFile(pathToFile);
    std::vector<sf::Vector2i> temp;
    if(openFile.is_open())
    {
        std::string tileLocation;
        openFile >> tileLocation;
        if(!texture.loadFromFile(tileLocation))
        {
            std::cout << "Could not load image file" << std::endl;
        }
        tiles.setTexture(texture);
        while(!openFile.eof())
        {
            std::string str, value;
            std::getline(openFile, str);
            std::stringstream stream(str);
            while(std::getline(stream, value, ' '))
            {
                if(value.length() > 0)
                {
                    std::string xx = value.substr(0, value.find(','));
                    std::string yy = value.substr(value.find(',') + 1);
                    int i, j;
                    for(i = 0; i < int(xx.length()); ++i)
                    {
                        if(!isdigit(xx[i]))
                            break;
                    }
                    for(j = 0; j < int(yy.length()); ++j)
                    {
                        if(!isdigit(yy[j]))
                            break;
                    }
                    int x = (i == int(xx.length())) ? atoi(xx.c_str()) : -1;
                    int y = (j == int(yy.length())) ? atoi(yy.c_str()) : -1;
                    sf::Vector2i tile(x, y);
                    temp.push_back(tile);
                }
            }
            map.push_back(temp);
            temp.clear();
        }
    }
    openFile.close();
}

void drawMap(const Map &map, sf::Sprite &tiles, sf::RenderWindow &window)
{
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
}

void printMap(const Map &map)
{
    std::cout << "Печатаем нашу карту" << std::endl;
    for(int i = 0; i < int(map.size()); ++i)
    {
        for(int j = 0; j < int(map[i].size()); ++j)
        {
            std::cout << "(" << map[i][j].x << "," << map[i][j].y << ") ";
        }
        std::cout << std::endl;
    }
}
