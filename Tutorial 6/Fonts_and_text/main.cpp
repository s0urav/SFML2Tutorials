#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <iostream>

int main()
{
    sf::Vector2i screenDimensions(800, 600);
    sf::Vector2i blockDimensions(10, 10);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "My first SFML game", sf::Style::Default);
    window.setPosition(sf::Vector2i(100, 100));
    //window.setKeyRepeatEnabled(false);
    sf::Font font;
    if(!font.loadFromFile("DroidSansMono.ttf"))
    {
        std::cout << "Could not load font!" << std::endl;
    }
    std::vector<sf::String> sentences;
    sf::String sentence;
    sentences.push_back(sentence);
    sf::Text textRow(sentence, font, 50);
    textRow.setColor(sf::Color(255, 0, 255));
    textRow.setPosition(10, 0);
    textRow.setStyle(sf::Text::Bold | sf::Text::Italic);
    std::vector<sf::Text> texts;
    texts.push_back(textRow);
    //int rowHeight = textRow.getGlobalBounds().height;
    //std::cout << "rowHeight = " << rowHeight << std::endl;
    int currIndex = 0;
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
                case sf::Event::TextEntered :
                    if(event.text.unicode >= 32 && event.text.unicode <= 126)
                    {
                        sentences[currIndex] += (char)event.text.unicode;
                        if(texts[currIndex].getGlobalBounds().width >= screenDimensions.x - 10)
                        {
                            sf::String sentence;
                            sentences.push_back(sentence);
                            texts.emplace_back(sf::Text(sentence, font, 50));
                            ++currIndex;
                            std::cout << "currIndex = " << currIndex << std::endl;
                            texts[currIndex].setColor(sf::Color(255, 0, 255));
                            texts[currIndex].setPosition(10, currIndex * (50));
                            texts[currIndex].setStyle(sf::Text::Bold | sf::Text::Italic);
                            texts[currIndex].setString(sentence);
                        }
                    }
                    else if(event.text.unicode == 8)
                    {
                        if(sentences[currIndex].getSize() > 0)
                            sentences[currIndex].erase(sentences[currIndex].getSize() - 1, sentences[currIndex].getSize());
                        else
                        {
                            if(sentences.size() > 1 && texts.size() > 1)
                            {
                                sentences.pop_back();
                                texts.pop_back();
                                currIndex = sentences.size() - 1;
                            }
                        }
                    }
                    texts[currIndex].setString(sentences[currIndex]);
                    break;
                default:
                    break;
            }
        }
        window.clear();
        // Прорисовка всех строчек текста
        for(const auto &text : texts)
            window.draw(text);
        window.display();
    }
    return 0;
}
