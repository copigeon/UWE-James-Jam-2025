#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "../Enums.h"

//guage has a max and min limit
//has a deccrease per time

class Gauge
{

public:
	Gauge();
	~Gauge();

	//GETTERS AND SETTERS
	sf::RectangleShape getGaugeBox();
	sf::RectangleShape getGaugeLeft();
	sf::RectangleShape getGaugeRight();
	sf::RectangleShape getGaugeMarker();

	//FUNCTIONS
	void updateGauge(int amount);
	void switchFillOrEmpty(bool booleanswitch);
	void initGaugeVisual(int height, int width, int min, int max, int current);
	void updateGaugeVisual();
	void flashBorder();

private:
	//size of gauge
	int scale = 100;
	//the minimum and maximum values for the guage
	int max = 70;
	int min = 20;
	//the starting or current value of the guage
	int current = 10;
	//the decrease amount and interval of decrease over time (decrease by 2 every 1 second, every 5 seconds etc)
	int decrease;
	//IF DECREASE OVER TIME - this is optional, a guage can decrease by intervention (action)
	int interval;
	//switch for if the gauge should be paused, default state is false
	bool pause = false;
	//default direction of guage is decrease, if gauge decrease is false the meter fills instead
	bool gauge_decrease = true;

	//default gauge sizes and position
	int height = 50;
	int width = 300;

	//CALCULATE BLOCK SIZE DEPENDING ON CHOSEN WIDTH OF GAUGE RECTANGLE
	// 300 / 100 = 3
	float chunk = width / scale;

	sf::Vector2f screen_position = sf::Vector2f(200,200);
	sf::Color gauge_colour = sf::Color::White;
	sf::Color gauge_out_colour = sf::Color::Yellow;

	//visual of gauge
	sf::RectangleShape gauge_box;
	sf::RectangleShape gauge_left;
	sf::RectangleShape gauge_right;
	sf::RectangleShape gauge_marker;

	//flash border
	sf::Clock flashing_clock;


};
