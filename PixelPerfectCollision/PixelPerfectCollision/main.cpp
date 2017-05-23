#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <stdlib.h>

enum class Direction {LEFT, RIGHT, UP, DOWN};
class Player
{
public:
    explicit Player(sf::Vector2f position, sf::Vector2f size, sf::Color color, const sf::Sound &sound);
    bool isCollision(const Player &other);
    void draw(sf::RenderWindow &window) const;
    void move(Direction dir, int speed);
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
    std::vector<std::vector<bool>> mask;
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

void Player::move(Direction dir, int speed)
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
    sf::String sentence("BoundBoxCollisionExample");
    sf::Text text(sentence, font, 50);
    text.setColor(sf::Color::Green);
    text.setPosition(50, 10);
    sf::SoundBuffer soundBuffer;
    if(!soundBuffer.loadFromFile("explosion.wav"))
    {
        std::cout << "Could not load sound file" << std::endl;
    }
    sf::Sound sound(soundBuffer);
    Player p1(sf::Vector2f(100, 100), sf::Vector2f(32, 32), sf::Color::Red, sound);
    Player p2(sf::Vector2f(200, 200), sf::Vector2f(45, 45), sf::Color::Blue, sound);
    p1.printInfo();
    p2.printInfo();
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
        {
            p1.move(Direction::LEFT, 2);
            if(p1.isCollision(p2))
                p1.move(Direction::RIGHT, 10);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            p1.move(Direction::UP, 2);
            if(p1.isCollision(p2))
                p1.move(Direction::DOWN, 10);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            p1.move(Direction::RIGHT, 2);
            if(p1.isCollision(p2))
                p1.move(Direction::LEFT, 10);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            p1.move(Direction::DOWN, 2);
            if(p1.isCollision(p2))
                p1.move(Direction::UP, 10);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            p2.move(Direction::RIGHT, 2);
            if(p2.isCollision(p1))
                p2.move(Direction::LEFT, 10);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            p2.move(Direction::LEFT, 2);
            if(p2.isCollision(p1))
                 p2.move(Direction::RIGHT, 10);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            p2.move(Direction::UP, 2);
            if(p2.isCollision(p1))
                p2.move(Direction::DOWN, 10);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            p2.move(Direction::DOWN, 2);
            if(p2.isCollision(p1))
                p2.move(Direction::UP, 10);
        }
        window.clear();
        window.draw(text);
        p1.draw(window);
        p2.draw(window);
        window.display();
    }
    return 0;
}
