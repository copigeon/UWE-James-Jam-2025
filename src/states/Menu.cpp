#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>;

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

	menu_name.setSize(sf::Vector2f(350, 250));
	menu_name.setPosition(sf::Vector2f(620, 450));
	if (!name_texture.loadFromFile("./Data/Images/menu_name.png")) { std::cout << "BG DID NOT LOAD" << std::endl; }
	menu_name.setTexture(&name_texture);

	map_graphics = {
		//UPDATE THIS MAP FROM ENUM
		{"foreground", menu_foreground},
		{"background",	menu_background},
		{"name", menu_name}
	};
}

void Menu::menuDraw()
{
	passed_window.draw(menu_background);
	passed_window.draw(menu_foreground);
	passed_window.draw(menu_name);
}

void Menu::animateSlide(Menu_Graphics graphic, float lapse, int movement_x, int movement_y, int x_end_pos, int y_end_pos)
{

	sf::RectangleShape& image = menu_foreground;
	switch (graphic) {
	case BACKGROUND:
	{
		//std::cout << "BACKGROUND SELECTED" << std::endl;
		image = menu_background;
		break;
	}
	case FOREGROUND:
	{
		//std::cout << "FOREGROUND SELECTED" << std::endl;
		image = menu_foreground;
		break;
	}
	}

	//sf::RectangleShape& image = map_graphics[graphic];

	if (image.getPosition() != sf::Vector2f(x_end_pos, y_end_pos)) {

		if (animation_clock.getElapsedTime().asSeconds() > lapse) {
			int check_x = std::abs(x_end_pos - movement_x);
			int check_y = std::abs(y_end_pos - movement_y);

			if (check_x < movement_x) {
				image.setPosition(sf::Vector2f(x_end_pos, image.getPosition().y));
			}
			else {

				image.setPosition(sf::Vector2f(image.getPosition().x + movement_x, image.getPosition().y + movement_y));
			}

			if (check_y < movement_y) {
				image.setPosition(sf::Vector2f(image.getPosition().x, y_end_pos));
			}
			else {
				image.setPosition(sf::Vector2f(image.getPosition().x + movement_x, image.getPosition().y + movement_y));
			}

			animation_clock.restart();
		}
	}
}

void Menu::flashGraphic(Menu_Graphics graphic, sf::Color colour, float lapse)
{
	sf::RectangleShape& image = menu_name;
	switch (graphic) {
	case NAME:
	{
		//std::cout << "BACKGROUND SELECTED" << std::endl;
		image = menu_name;
		break;
	}
	}

	if (flash_clock.getElapsedTime().asSeconds() > lapse) {
		if (flash) {
			image.setFillColor(colour);
			flash = false;
		}
		else {
			image.setFillColor(sf::Color::White);
			flash = true;
		}
		flash_clock.restart();
	}
}

