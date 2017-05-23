#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My first SFML game", sf::Style::Default);
    sf::Vector2u size(400, 400);
    window.setSize(size);
    window.setTitle("New title");
    window.setPosition(sf::Vector2i(100, 100));
    sf::Clock clock;
    sf::Time time2;
    sf::Time time = sf::seconds(2);
    time += sf::milliseconds(5000);
    //std::cout << "time = " << time.asSeconds() << std::endl;
    //std::cout << "Press key to continue" << std::endl;
    std::string message = "Hello my name is Igor";
    std::string output = "";
    sf::RectangleShape rect(sf::Vector2f(20, 20));
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(100, 100);
    int index = 0;
    //window.setKeyRepeatEnabled(false);
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::TextEntered :
                if(event.text.unicode != 8)
                {
                    output += static_cast<char>(event.text.unicode);
                }
                else
                {
                    output = output.substr(0, output.length() - 1);
                    system("clear");
                    std::cout << output << std::endl;
                }
                break;
            case sf::Event::GainedFocus :
                std::cout << "Window is active!" << std::endl;
                break;
            case sf::Event::LostFocus :
                std::cout << "Window is not active." << std::endl;
                break;
            case sf::Event::Resized :
                std::cout << "Window was resized. Width = " << event.size.width << " Height = " << event.size.height;
                break;
            case sf::Event::MouseEntered :
                std::cout << "Mouse is within screen bounds" << std::endl;
                break;
            case sf::Event::MouseLeft :
                std::cout << "Mouse is not within screen bounds" << std::endl;
                break;
            case sf::Event::MouseMoved :
                //std::cout << "Moouse curcor coordinates x = " << event.mouseMove.x << " y = " << event.mouseMove.y << std::endl;
                break;
            case sf::Event::MouseButtonPressed :
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "Left button was pressed at x = " << event.mouseButton.x << " y = " << event.mouseButton.y << std::endl;
                }
                else if(event.mouseButton.button == sf::Mouse::Middle)
                {
                    std::cout << "Middle button was pressed at x = " << event.mouseButton.x << " y = " << event.mouseButton.y << std::endl;
                }
                else if(event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "Right button was pressed x = " << event.mouseButton.x << " y = " << event.mouseButton.y << std::endl;
                }
            case sf::Event::MouseWheelMoved :
            {
                std::cout << "Mouse wheel was moved delta = " << event.mouseWheel.delta << std::endl;
            }
            default:
                break;
            }
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Q)
                    window.close();
                if(event.key.code == sf::Keyboard::Return && event.key.alt)
                {
                    system("clear");
                    output += message[index++];
                    std::cout << output << std::endl;
                }

            }
        }

        /*if(window.waitEvent(event))
        {
            std::cout << "Event activated" << std::endl;
        }*/
        time2 = clock.getElapsedTime();
        std::cout << "time2 = " << time2.asMilliseconds() << std::endl;
        time2 = clock.restart();
        window.clear();
        window.draw(rect);
        window.display();
    }
    return 0;
}
