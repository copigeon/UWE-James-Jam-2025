#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "Menu.h"
#include "../Enums.h"

Menu::Menu(sf::RenderWindow& game_window)
	: passed_window(game_window)
{
}

Menu::~Menu()
{
}

void Menu::initMenu()
{
	menu_background.setSize(sf::Vector2f(passed_window.getSize().x, passed_window.getSize().y));
	menu_background.setPosition(sf::Vector2f(0, 0));
	if (!menu_texture.loadFromFile("./Data/Images/menu_1.png")) { std::cout << "BG DID NOT LOAD" << std::endl; }
	menu_background.setTexture(&menu_texture);

	menu_foreground.setSize(sf::Vector2f(passed_window.getSize().x, passed_window.getSize().y));
	menu_foreground.setPosition(sf::Vector2f(-500, 0));
	if (!foreground_texture.loadFromFile("./Data/Images/menu_2.png")) { std::cout << "BG DID NOT LOAD" << std::endl; }
	menu_foreground.setTexture(&foreground_texture);
}

void Menu::menuDraw()
{
	passed_window.draw(menu_background);
	passed_window.draw(menu_foreground);
}

void Menu::menuAnimate()
{
	if (menu_foreground.getPosition().x < -100) {
		if (animate.getElapsedTime().asSeconds() > 0.1) {
			menu_foreground.setPosition(sf::Vector2f(menu_foreground.getPosition().x + 5, 0));
			animate.restart();
		}
	}
}
