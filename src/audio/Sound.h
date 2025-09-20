#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "../Enums.h"

class Sound
{
public:
	Sound();
	~Sound();

	//GETTERS AND SETTERS
	int& getVolume();
	void setVolume(int new_volume);
	std::string getPath();
	void setPath(std::string new_path);
	sf::SoundBuffer& getBuffer();
	void setBuffer(sf::SoundBuffer& new_buffer);
	Audiotypes& getType();
	void setType(Audiotypes new_type);

	//FUNCTIONS
	void loadBuffer(std::string file_name);

private:

	int volume = 10;
	sf::SoundBuffer buffer;
	Audiotypes type = Audiotypes::SFX;
	std::string path;
};
