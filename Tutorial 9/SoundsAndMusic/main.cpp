#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My first SFML game", sf::Style::Default);
    window.setPosition(sf::Vector2i(100, 100));
    sf::RectangleShape rect(sf::Vector2f(20, 20));
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(100, 100);
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;
    if(!soundBuffer.loadFromFile("TankMov.wav"))
    {
        std::cout << "Could not load background sound" << std::endl;
    }
    sound.setBuffer(soundBuffer);
    sound.setLoop(true);
    bool isPaused = false;

    sf::Music music;
    if(!music.openFromFile("mario_background.ogg"))
    {
        std::cout << "Could not load music!" << std::endl;
    }
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed :
                    if(event.key.code == sf::Keyboard::Escape)
                        window.close();
                    if(event.key.code == sf::Keyboard::P)
                        music.play();
                    if(event.key.code == sf::Keyboard::Space)
                    {
                        isPaused = !isPaused;
                        if(isPaused)
                            music.pause();
                        else
                            music.play();
                    }
                    if(event.key.code == sf::Keyboard::S)
                        music.stop();
                    if(event.key.code == sf::Keyboard::Add)
                        music.setVolume(music.getVolume() + 5.0f);
                    if(event.key.code == sf::Keyboard::Subtract)
                        music.setVolume(sound.getVolume() - 5.0f);
                    break;
                default:
                    break;
            }
        }
        window.clear();
        window.draw(rect);
        window.display();
    }
    return 0;
}
