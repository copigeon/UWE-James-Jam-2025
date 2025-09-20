#pragma once
#include "Sound.h"

Sound::Sound()
{

}

Sound::~Sound()
{

}

int& Sound::getVolume()
{
	return volume;
}

void Sound::setVolume(int new_volume)
{
	volume = new_volume;
}

std::string Sound::getPath()
{
	return path;
}

void Sound::setPath(std::string new_path)
{
	path = new_path;
}

sf::SoundBuffer& Sound::getBuffer()
{
	return buffer;
}

void Sound::setBuffer(sf::SoundBuffer& new_buffer)
{
	buffer = new_buffer;
}

Audiotypes& Sound::getType()
{
	return type;
}

void Sound::setType(Audiotypes new_type)
{
	type = new_type;
}

void Sound::loadBuffer(std::string file_name)
{
	std::cout << "load buffer" << std::endl;
	if (buffer.getSampleCount() == 0) {
		std::cout << "sound object is loading buffer..." << std::endl;
		if (!buffer.loadFromFile(file_name)) {
			std::cout << "sound object sound file not found" << std::endl;
		}
		else {
			std::cout << "sound object sound is loaded" << std::endl;
		}
	}
}