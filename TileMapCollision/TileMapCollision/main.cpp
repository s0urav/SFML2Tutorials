#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <sstream>

enum class Direction {STOP, LEFT, RIGHT, UP, DOWN};
typedef std::vector<std::vector<int>> Map;

void loadMap(const std::string &pathToFile, Map &map, sf::Texture &texture, sf::Sprite &tiles);

void drawMap(sf::RenderWindow &window, const Map &map, sf::Sprite &tiles);

class Player
{
public:
    explicit Player(sf::Vector2f position, sf::Vector2f size, sf::Color color, const sf::Sound &sound);
    bool isCollision(const Player &other);
    bool isTileMapCollision(const Map &map);
    bool isTileMapCollision_advanced(const Map &map);
    void draw(sf::RenderWindow &window) const;
    void turn(Direction dir);
    void reverse();
    void move(int speed);
    void printInfo() const;
    void update();
    inline float getX() const {return rect.getPosition().x; }
    inline float getY() const {return rect.getPosition().y; }
    inline float getTop() const {return top; }
    inline float getBottom() const {return bottom; }
    inline float getLeft() const {return left; }
    inline float getRight() const {return right; }
    inline std::vector<std::vector<bool>> getMask() const {return mask;}
private:
    sf::Sound sound;
    sf::Color color;
    sf::RectangleShape rect;
    float left, right, top, bottom;
    std::vector<sf::Vector2i> tiles;
    std::vector<std::vector<bool>> mask;
    Direction dir = Direction::RIGHT;
};

Player::Player(sf::Vector2f position, sf::Vector2f size, sf::Color color, const sf::Sound &sound) :
        sound(sound), color(color)
{
    rect.setPosition(position);
    rect.setSize(size);
    rect.setFillColor(color);

    sf::Image image;
    sf::RenderTexture rTexture;
    sf::Texture texture;

    rTexture.create(size.x, size.y);
    sf::RectangleShape tempRect(rect);
    tempRect.setPosition(0, 0);
    rTexture.draw(tempRect);
    rTexture.display();
    texture = rTexture.getTexture();
    image = texture.copyToImage();
    for(int i = 0; i < int(image.getSize().x); ++i)
    {
        std::vector<bool> tempMask;
        for(int j = 0; j < int(image.getSize().y); ++j)
            tempMask.push_back(image.getPixel(i, j).a > 0);
        mask.push_back(tempMask);
    }
    update();
}

void Player::update()
{
    left = rect.getPosition().x;
    right = rect.getPosition().x + rect.getSize().y;
    top = rect.getPosition().y;
    bottom = rect.getPosition().y + rect.getSize().y;

    sf::Vector2i topLeft((int)left / 30, (int)top / 30);
    sf::Vector2i topRight((int)right / 30, (int)top / 30);
    sf::Vector2i bottomLeft((int)left / 30, (int)bottom / 30);
    sf::Vector2i bottomRight((int)right / 30, (int)bottom / 30);
    tiles.clear();
    tiles.push_back(topLeft);
    //Проверки нужны для того чтобы не хранить одинаковых экземпляров угловых тайлов
    //с которыми контактирует игрок, например если он находится в пределах одного тайла,
    //то все четыре угловых тайла были бы одинаковыми, и воизбежание этого перед добавлением
    //нового тайла мы проверяем не находится ли он уже в векторе соседствующих с игроком угловых тайлов
    if(std::find(tiles.begin(), tiles.end(), topRight) == tiles.end()) tiles.push_back(topRight);
    if(std::find(tiles.begin(), tiles.end(), bottomLeft) == tiles.end()) tiles.push_back(bottomLeft);
    if(std::find(tiles.begin(), tiles.end(), bottomRight) == tiles.end()) tiles.push_back(bottomRight);
}

bool Player::isCollision(const Player &other)
{
    //right < other.left || left > other.right || top > other.bottom || bottom < other.top
    if(right < other.getLeft() || left > other.getRight() ||
       top > other.getBottom() || bottom < other.getTop())
    {
        return false;
    }
    else
    {
        float colBottom, colTop, colLeft, colRight;
        colBottom = std::min(bottom, other.getBottom());
        colTop = std::max(top, other.getTop());
        colLeft = std::max(left, other.getLeft());
        colRight = std::min(right, other.getRight());
        for(int x = colLeft; x < colRight; ++x)
        {
            for(int y = colTop; y < colBottom; ++y)
                if(mask[x - left][y - top] && other.getMask()[x - other.getLeft()][y - other.getTop()])
                {
                    sound.play();
                    return true;
                }
        }
        return false;
    }
}

bool Player::isTileMapCollision(const Map &map)
{
    //Эта функция-член проверяет столкновения игрока со всеми тайлами карты,
    //т.е. она неэффективная
    bool result = false;
    for(int i = 0; i < int(map.size()); ++i)
    {
        for(int j = 0; j < int(map[i].size()); ++j)
            {
                if(map[i][j] != 0)
                {
                    float tileLeft = j * 30, tileRight = j * 30 + 30, tileTop = i * 30, tileBottom = i * 30 + 30;
                    if(right < tileLeft || left > tileRight || top > tileBottom || bottom < tileTop)
                    {
                       rect.setFillColor(color);
                    }
                    else
                    {
                        rect.setFillColor(sf::Color::White);
                        sound.play();
                        result = true;
                        break;
                    }
                }
            }
        }
    return result;
}

bool Player::isTileMapCollision_advanced(const Map &map)
{
    //Эта функция-член более эффективная т.к. проверяет столкновения игрока
    // только с соседними тайлами
    bool result = false;
    for(auto tile : tiles)
    {
        if(tile.y >= 0 && tile.y < int(map.size()))
        {
            if(tile.x >= 0 && tile.x < map.at(tile.y).size())
            {
                if(map.at(tile.y).at(tile.x))
                {
                    rect.setFillColor(sf::Color::White);
                    sound.play();
                    result = true;
                    //Ести есль коллизия хоть с одним из окружающих тайлов то проверять столкновения
                    //с остальными нет смысла и мы прерываем цикл
                    break;
                }
                else
                {
                  rect.setFillColor(color);
                }
            }
        }

    }
    return result;
}

void Player::turn(Direction dir)
{
    this->dir = dir;
}

void Player::reverse()
{
    switch(dir)
    {
        case Direction::UP :
            turn(Direction::DOWN);
            break;
        case Direction::DOWN :
            turn(Direction::UP);
            break;
        case Direction::LEFT :
            turn(Direction::RIGHT);
            break;
        case Direction::RIGHT :
            turn(Direction::LEFT);
            break;
        default:
            break;
    }
}

void Player::move(int speed)
{
    switch(dir)
    {
        case Direction::UP :
            rect.move(0, -speed);
            break;
        case Direction::DOWN :
            rect.move(0, speed);
            break;
        case Direction::LEFT :
            rect.move(-speed, 0);
            break;
        case Direction::RIGHT :
            rect.move(speed, 0);
            break;
        default:
            break;
    }
    update();
}

void Player::draw(sf::RenderWindow &window) const
{
    window.draw(rect);
}

void Player::printInfo() const
{
    std::cout << "----------------------------" << std::endl;
    std::cout << "Позиция x = " << getX() << " y = " << getY() << std::endl;
}

int main()
{
    sf::Vector2i size(800, 600);
    sf::RenderWindow window(sf::VideoMode(size.x, size.y), "BoundingBoxCollisions", sf::Style::Default);
    window.setPosition(sf::Vector2i(100, 100));
    sf::Font font;
    if(!font.loadFromFile("DroidSansMono.ttf"))
    {
        std::cout << "Could not load font!" << std::endl;
    }
    sf::String sentence("TilemapCollisionExample");
    sf::Text text(sentence, font, 50);
    text.setColor(sf::Color::Green);
    text.setPosition(50, 5);
    sf::SoundBuffer soundBuffer;
    if(!soundBuffer.loadFromFile("explosion.wav"))
    {
        std::cout << "Could not load sound file" << std::endl;
    }
    sf::Sound sound(soundBuffer);
    Player p1(sf::Vector2f(500, 300), sf::Vector2f(25, 25), sf::Color::Red, sound);
    Player p2(sf::Vector2f(400, 150), sf::Vector2f(25, 25), sf::Color::Blue, sound);
    p1.printInfo();
    p2.printInfo();
    Map map;
    sf::Texture texture;
    sf::Sprite tiles;
    loadMap("map.txt", map, texture, tiles);

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
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Escape :
                            window.close();
                            break;
                        default:
                            break;
                    }
                    break;
                default :
                    break;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            p1.turn(Direction::LEFT);
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            p1.turn(Direction::UP);
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            p1.turn(Direction::RIGHT);
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            p1.turn(Direction::DOWN);
        else
            p1.turn(Direction::STOP);
        p1.move(1);
        if(p1.isCollision(p2) || p1.isTileMapCollision_advanced(map))
        {
            p1.reverse();
            p1.move(2);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            p2.turn(Direction::RIGHT);
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            p2.turn(Direction::LEFT);
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            p2.turn(Direction::UP);
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            p2.turn(Direction::DOWN);
        else
            p2.turn(Direction::STOP);
        p2.move(1);
        if(p2.isCollision(p1) || p2.isTileMapCollision_advanced(map))
        {
            p2.reverse();
            p2.move(2);
        }
        window.clear(sf::Color(0, 180, 200));
        window.draw(text);
        drawMap(window, map, tiles);
        p1.draw(window);
        p2.draw(window);
        window.display();
    }
    return 0;
}

void loadMap(const std::string &pathToFile, Map &map, sf::Texture &texture, sf::Sprite &tiles)
{
    if(!map.empty())
        map.clear();
    std::ifstream openFile(pathToFile);
    std::vector<int> temp;
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
                    int tile = atoi(value.c_str());
                    temp.push_back(tile);
                }
            }
            map.push_back(temp);
            temp.clear();
        }
    }
    openFile.close();
}

void drawMap(sf::RenderWindow &window, const Map &map, sf::Sprite &tiles)
{
    for(int i = 0; i < int(map.size()); ++i)
    {
        for(int j = 0; j < int(map[i].size()); ++j)
        {
            //std::cout << map[i][j];
            tiles.setPosition(j * 30, i * 30);
            switch (map[i][j]) {
                case 1:
                    tiles.setTextureRect(sf::IntRect(0, 0, 30, 30));
                    window.draw(tiles);
                    break;
                case 2:
                    tiles.setTextureRect(sf::IntRect(30, 0, 30, 30));
                    window.draw(tiles);
                    break;
                case 3:
                    tiles.setTextureRect(sf::IntRect(0, 30, 30, 30));
                    window.draw(tiles);
                    break;
                case 4:
                    tiles.setTextureRect(sf::IntRect(30, 30, 30, 30));
                    window.draw(tiles);
                    break;
                default:
                    break;
            }
        }
        //std::cout << std::endl;
    }
}
