#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "../Enums.h"

class Menu
{
public:
	Menu(sf::RenderWindow& game_window);
	~Menu();

	//GETTERS AND SETTERS

	//FUNCTIONS

	void initMenu();
	void menuDraw();

	void menuAnimate();

private:

	sf::RectangleShape menu_background;
	sf::Texture menu_texture;
	sf::RectangleShape menu_foreground;
	sf::Texture foreground_texture;

	sf::RenderWindow& passed_window;

	sf::Clock animate;
};