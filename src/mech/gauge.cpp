#pragma once
#include "Gauge.h"

Gauge::Gauge()
{

}

Gauge::~Gauge()
{

}

sf::RectangleShape Gauge::getGaugeLeft()
{
	return gauge_left;
}

sf::RectangleShape Gauge::getGaugeRight()
{
	return gauge_right;
}

sf::RectangleShape Gauge::getGaugeMarker()
{
	return gauge_marker;
}

sf::RectangleShape Gauge::getGaugeBox()
{
	return gauge_box;
}

void Gauge::updateGauge(int amount)
{
	switch (gauge_decrease) {
	case true:
	{
		if (current >= 0) {
			current = current - amount;
		}
		break;
	}
	case false:
	{
		if (current < scale) {
			current = current + amount;
		}
		break;
	}
	}
}

void Gauge::updateGauge()
{
	if (pause == 0) {
		if (update_clock.getElapsedTime().asSeconds() > 1) {
			if (current >= 0 && current < scale) {
				switch (gauge_decrease) {
				case true:
				{
					current = current - interval;
					break;
				}
				case false:
				{
					current = current + interval;
					break;
				}
				}
			}
			update_clock.restart();
		}
	}
	else {
		if (pause_clock.getElapsedTime().asSeconds() > 1) {
			pause--;
			pause_clock.restart();
		}
	}
}

void Gauge::switchFillOrEmpty(bool booleanswitch)
{
	gauge_decrease = booleanswitch;
}

void Gauge::initGaugeVisual(int new_height, int new_width, int new_min, int new_max, int new_current, int new_interval)
{
	chunk = new_width / scale;
	current = new_current;
	height = new_height;
	width = new_width;
	min = new_min;
	max = new_max;
	interval = new_interval;

	gauge_box.setSize(sf::Vector2f(width, height));
	gauge_box.setPosition(screen_position);
	gauge_box.setFillColor(sf::Color::White);
	gauge_box.setOutlineThickness(5);
	gauge_box.setOutlineColor(sf::Color::Blue);

	int left_width = (chunk * min);
	gauge_left.setSize(sf::Vector2f(left_width, height));
	gauge_left.setPosition(sf::Vector2f(gauge_box.getPosition().x, gauge_box.getPosition().y));
	gauge_left.setFillColor(gauge_out_colour);

	int right_width = (chunk * (scale-max));
	gauge_right.setSize(sf::Vector2f(right_width, height));
	int right_width_pos = (chunk * max);
	int temp_position = gauge_box.getPosition().x + right_width_pos;
	gauge_right.setPosition(sf::Vector2f(temp_position, gauge_box.getPosition().y));
	gauge_right.setFillColor(gauge_out_colour);

	int temp_position_2 = gauge_box.getPosition().x + (chunk*current);
	gauge_marker.setSize(sf::Vector2f(chunk*10, height));
	gauge_marker.setPosition(sf::Vector2f(temp_position_2, gauge_box.getPosition().y));
	gauge_marker.setFillColor(sf::Color::Green);

}

void Gauge::updateGaugeVisual()
{

	if (current >= 0 && current < scale - 9) {
		int temp_position = gauge_box.getPosition().x + (chunk * current);
		gauge_marker.setPosition(sf::Vector2f(temp_position, gauge_box.getPosition().y));
	}

	if (current >= 0 && current < scale) {
		if (pause > 0) {
			gauge_box.setOutlineColor(sf::Color::Blue);
			gauge_marker.setFillColor(sf::Color::Blue);
		}
		else {
			if (current > min && current < max) {
				if (gauge_decrease) {
					gauge_box.setOutlineColor(sf::Color::Red);
					gauge_marker.setFillColor(sf::Color::Red);
				}
				else {
					gauge_box.setOutlineColor(sf::Color::Green);
					gauge_marker.setFillColor(sf::Color::Green);

				}
			}
		}
	}
}

void Gauge::flashBorder()
{
	if (current < min) {
		if (flashing_clock.getElapsedTime().asSeconds() > 0.5) {

			if (gauge_box.getOutlineColor() == sf::Color::Red) {
				gauge_box.setOutlineColor(sf::Color::Magenta);
			}
			else {
				gauge_box.setOutlineColor(sf::Color::Red);
			}
			flashing_clock.restart();
		}
	}
	else if (current > max) {
		if (flashing_clock.getElapsedTime().asSeconds() > 0.5) {

			if (gauge_box.getOutlineColor() == sf::Color::Green) {
				gauge_box.setOutlineColor(sf::Color::Magenta);
			}
			else {
				gauge_box.setOutlineColor(sf::Color::Green);
			}
			flashing_clock.restart();
		}
	}
	else {
		return;
	}
}

void Gauge::pauseGauge(int time)
{
	pause = time;
}

