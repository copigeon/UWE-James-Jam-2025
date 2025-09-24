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

	void animateSlide(Menu_Graphics graphic, float lapse, int movement_x, int movement_y, int x_end_pos, int y_end_pos);

private:

	sf::RectangleShape menu_background;
	sf::Texture menu_texture;
	sf::RectangleShape menu_foreground;
	sf::Texture foreground_texture;

	sf::RenderWindow& passed_window;

	sf::Clock animation_clock;

	Menu_Graphics graphics;
};