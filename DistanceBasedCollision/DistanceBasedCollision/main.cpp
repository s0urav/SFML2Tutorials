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
    explicit Player(sf::Vector2f position, float radius, sf::Color color, const sf::Sound &sound);
    bool isCollision(const Player &other);
    void draw(sf::RenderWindow &window) const;
    void move(Direction dir, int speed);
    void printInfo() const;
    inline float getX() const {return circle.getPosition().x; }
    inline float getY() const {return circle.getPosition().y; }
    inline float getR() const {return circle.getRadius(); }
private:
    sf::Sound sound;
    sf::Color color;
    sf::CircleShape circle;
};

Player::Player(sf::Vector2f position, float radius, sf::Color color, const sf::Sound &sound) :
        sound(sound), color(color)
{
    circle.setPosition(position);
    circle.setOrigin(sf::Vector2f(radius, radius));
    circle.setRadius(radius);
    circle.setFillColor(color);
}

bool Player::isCollision(const Player &other)
{
    bool result;
    float distance2 = sqrt(pow(getX() - other.getX(), 2) + pow(getY() - other.getY(), 2));
    if(distance2 > getR() + other.getR())
    {
        result = false;
        std::cout << "Дистанция - " << distance2 << std::endl;
        this->printInfo();
        other.printInfo();
        circle.setFillColor(color);
    }
    else
    {
        result = true;
        std::cout << "Collision " << std::endl;
        this->printInfo();
        other.printInfo();
        sound.play();
        circle.setFillColor(sf::Color::Magenta);
    }
    return result;
}

void Player::move(Direction dir, int speed)
{
    switch(dir)
    {
        case Direction::UP :
            circle.move(0, -speed);
            break;
        case Direction::DOWN :
            circle.move(0, speed);
            break;
        case Direction::LEFT :
            circle.move(-speed, 0);
            break;
        case Direction::RIGHT :
            circle.move(speed, 0);
            break;
    }
}

void Player::draw(sf::RenderWindow &window) const
{
    window.draw(circle);
}

void Player::printInfo() const
{
    std::cout << "----------------------------" << std::endl;
    std::cout << "Радиус = " << getR() << std::endl;
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
    Player p1(sf::Vector2f(100, 100), 15, sf::Color::Red, sound);
    Player p2(sf::Vector2f(200, 200), 30, sf::Color::Blue, sound);
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
