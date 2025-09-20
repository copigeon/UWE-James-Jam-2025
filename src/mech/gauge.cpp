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
		current = current - amount;
		break;
	}
	case false:
	{
		current = current + amount;
		break;
	}
	}
}

void Gauge::switchFillOrEmpty(bool booleanswitch)
{
	gauge_decrease = booleanswitch;
}

void Gauge::initGaugeVisual()
{
	gauge_box.setSize(sf::Vector2f(width, height));
	gauge_box.setPosition(screen_position);
	gauge_box.setFillColor(sf::Color::White);
	//gauge_box.setOutlineThickness(5);
	gauge_box.setOutlineColor(sf::Color::Blue);

	int left_width = (chunk * min);
	gauge_left.setSize(sf::Vector2f(left_width, height));
	gauge_left.setPosition(sf::Vector2f(gauge_box.getPosition().x, gauge_box.getPosition().y + 10));
	gauge_left.setFillColor(gauge_out_colour);

	int right_width = width - (chunk*max);
	gauge_right.setSize(sf::Vector2f(right_width, height));
	int temp_position = gauge_box.getPosition().x + (gauge_box.getSize().length() - right_width);
	gauge_right.setPosition(sf::Vector2f(temp_position, gauge_box.getPosition().y+10));
	gauge_right.setFillColor(gauge_out_colour);

	temp_position = gauge_box.getPosition().x + (chunk*current);
	gauge_marker.setSize(sf::Vector2f(chunk*10, height));
	gauge_marker.setPosition(sf::Vector2f(temp_position, gauge_box.getPosition().y + 10));
	gauge_marker.setFillColor(sf::Color::Green);

}

void Gauge::updateGaugeVisual()
{
	int temp_position = gauge_box.getPosition().x + current;
	gauge_marker.setPosition(sf::Vector2f(temp_position, gauge_box.getPosition().y));

	if (pause) {
		gauge_box.setOutlineColor(sf::Color::Blue);
	}
	else {
		if (gauge_decrease) {
			gauge_box.setOutlineColor(sf::Color::Red);
		}
		else {
			gauge_box.setOutlineColor(sf::Color::Green);
		}
	}

}

