#pragma once

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Threadpool.h"
#include "audio/Sound.h"
#include "audio/Audio.h"

class Game
{
public:
	Game(sf::Window& window);
	~Game();
	bool init();
	void update(float dt);
	void render();

	//EVENTS
	//MOUSE
	void mousePressed(std::optional<sf::Event> event);
	void mouseReleased(std::optional<sf::Event> event);
	void mouseEntered(std::optional<sf::Event> event);
	void mouseLeft(std::optional<sf::Event> event);
	void mouseMoved(std::optional<sf::Event> event);
	void mouseMovedRaw(std::optional<sf::Event> event);
	void mouseWheelScrolled(std::optional<sf::Event> event);
	//KEY
	void keyPressed(std::optional<sf::Event> event);
	void keyReleased(std::optional<sf::Event> event);
	//TOUCH
	void touchBegan(std::optional<sf::Event> event);
	void touchEnd(std::optional<sf::Event> event);
	void touchMoved(std::optional<sf::Event> event);
	//JOYSTICK
	void JoystickButtonPressed(std::optional<sf::Event> event);
	void joystickButtonReleased(std::optional<sf::Event> event);
	void JoystickConnected(std::optional<sf::Event> event);
	void joystickDisconnected(std::optional<sf::Event> event);
	void joystickMoved(std::optional<sf::Event> event);

	//THREADPOOL
	ThreadPool tpool{ 2 };
	ThreadPool tpool_pathfinding{ 2 };

	//AUDIO
	//TEST
	Audio audio_manager;
	std::shared_ptr<Sound> test;
	std::shared_ptr<Sound> test2;
	std::shared_ptr<Sound> test3;


private:
	sf::Window& window;
	
};
