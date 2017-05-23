#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <cmath>
#include <ctime>
#include <stdlib.h>

enum class Direction {LEFT, RIGHT, UP, DOWN};
class Player
{
public:
    explicit Player(sf::Vector2f position, sf::Vector2f size, sf::Color color, const sf::Sound sound);
    void update();
    bool isCollision(const Player &other);
    void draw(sf::RenderWindow &window) const;
    void printInfo() const;
    void move(Direction dir, int speed);
    inline float getLeft() const {return left;}
    inline float getRight() const {return right;}
    inline float getTop() const {return top;}
    inline float getBottom() const {return bottom;}
private:
    sf::RectangleShape rect;
    float bottom, left, right, top;
    sf::Sound sound;
};

Player::Player(sf::Vector2f position, sf::Vector2f size, sf::Color color, const sf::Sound sound)
{
    rect.setPosition(position);
    rect.setSize(size);
    rect.setFillColor(color);
    update();
    this->sound = sound;
}

void Player::update()
{
    bottom = rect.getPosition().y + rect.getSize().y;
    left = rect.getPosition().x;
    right = rect.getPosition().x + rect.getSize().x;
    top = rect.getPosition().y;
}

bool Player::isCollision(const Player &other)
{
    bool result = false;
    if(right < other.left || left > other.right || top > other.bottom || bottom < other.top)
    {
        result = false;
    }
    else
    {
        result = true;
        sound.play();
    }
    return result;
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
    this->update();
}

void Player::draw(sf::RenderWindow &window) const
{
    window.draw(rect);
}

void Player::printInfo() const
{
    std::cout << "l = " << left << " r = " << right << " t = " << top << " b = " << bottom << std::endl;
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
    Player p2(sf::Vector2f(400, 400), sf::Vector2f(32, 32), sf::Color::Blue, sound);
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
                p1.move(Direction::RIGHT, 32);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            p1.move(Direction::UP, 2);
            if(p1.isCollision(p2))
                p1.move(Direction::DOWN, 32);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            p1.move(Direction::RIGHT, 2);
            if(p1.isCollision(p2))
                p1.move(Direction::LEFT, 32);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            p1.move(Direction::DOWN, 2);
            if(p1.isCollision(p2))
                p1.move(Direction::UP, 32);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            p2.move(Direction::RIGHT, 2);
            if(p2.isCollision(p1))
                p2.move(Direction::LEFT, 32);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            p2.move(Direction::LEFT, 2);
            if(p2.isCollision(p1))
                 p2.move(Direction::RIGHT, 32);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            p2.move(Direction::UP, 2);
            if(p2.isCollision(p1))
                p2.move(Direction::DOWN, 32);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            p2.move(Direction::DOWN, 2);
            if(p2.isCollision(p1))
                p2.move(Direction::UP, 32);
        }
        window.clear();
        window.draw(text);
        p1.draw(window);
        p2.draw(window);
        window.display();
    }
    return 0;
}
