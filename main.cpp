/*
* Author: SHAHAR ANKONINA
* DATE: 11/04/2025
*/

#include "GameManager.h"

#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 500, 500 }), "Chess");
    GameManager gm;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::Resized>()) {
                sf::FloatRect viewRect = sf::FloatRect({ 0, 0 }, { static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) });
                window.setView(sf::View(viewRect));
            }
        }

        window.clear();
        gm.Update(window); // Draws the game
        window.display();
    }
}