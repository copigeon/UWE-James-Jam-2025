#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "Audio.h"
#include "../Structs.h"

Audio::Audio()
{
}

Audio::~Audio()
{
}

void Audio::initSounds()
{
	//READ IN THE INIT SOUNDS TEXT FILE
	std::ifstream file("./Data/Sounds/init_sounds.txt");
	std::string line;

	if (file.is_open()) {
		while (getline(file, line)) {
			std::cout << line << std::endl;

			std::string delimiter = ",";
			size_t pos = 0;
			std::string token;
			std::string parts[3];
			int j = 0;

			//BREAK DOWN BY DELIMITER INTO PARTS ARRAY
			while ((pos = line.find(delimiter)) != std::string::npos && j < 2) {
				token = line.substr(0, pos);
				line.erase(0, pos + delimiter.length());
				parts[j++] = token;
			}
			// FINAL PART AFTER DELIMITER
			parts[j] = line;

			// SET PARTS TO VARIABLES TO BUILD SOUND
			std::string name = parts[0];
			std::string typeStr = parts[1];
			std::string path = parts[2];

			//std::cout << "Name: " << name << "\n";
			//std::cout << "Type: " << typeStr << "\n";
			//std::cout << "Path: " << path << "\n";

			//BUILD THE SOUND OBJECT AND STORE IN AUDIO MANAGER SOUND MAP
			auto newSound = std::make_shared<Sound>();
			newSound->setType(strtoType(typeStr));
			newSound->loadBuffer(path);
			newSound->setPath(path);

			map_sounds[name] = newSound;
		}
		file.close();
	}
	else {
		std::cerr << "Unable to open file!" << std::endl;
	}
}

Audiotypes Audio::strtoType(std::string& str)
{
	std::unordered_map<std::string, Audiotypes> map = {
		//UPDATE THIS MAP FROM ENUM
		{"SFX",       Audiotypes::SFX},
		{"ENVIRO",    Audiotypes::ENVIRO},
		{"NPC",       Audiotypes::NPC},
		{"PLAYER",    Audiotypes::PLAYER},
		{"NARRATIVE", Audiotypes::NARRATIVE}
	};

	auto it = map.find(str);
	if (it != map.end()) { return it->second; }

	std::cerr << "Unknown Audiotype: " << str << ", defaulting to SFX.\n";
	return Audiotypes::SFX;
}

std::map<std::string, std::shared_ptr<Sound>>& Audio::getSounds()
{
	return map_sounds;
}

void Audio::playSounds()
{
	//VOLUME IS SET DEPENDING ON WHAT TYPE OF AUDIO IS NEEDING TO BE PLAYED
	//TO DO - DECIDE THE PLAY PRIORITY OF SOUNDS

	for (auto& entry : audio_queue) {
		if (entry.struct_sound) {
			entry.struct_sfsound.setVolume(volume);
		}
	}

	if (isPlaying(Audiotypes::SFX)) {
		//std::cout << "SFX IS PLAYING " << std::endl;
		fadeVolumeOut(volume);
		for (auto& entry : audio_queue) {
			if (entry.struct_sound && entry.struct_sound->getType() != Audiotypes::SFX) {
				entry.struct_sfsound.setVolume(volume);
			}
		}
	}
	else {
		//std::cout << "SFX IS NOT PLAYING " << std::endl;
		fadeVolumeIn(volume);
		for (auto& entry : audio_queue) {
			if (entry.struct_sound && entry.struct_sound->getType() != Audiotypes::SFX) {
				entry.struct_sfsound.setVolume(volume);
			}
		}
	}

	for (int i = static_cast<int>(sfx_pool.size()) - 1; i >= 0; i--) {
		
	}

	for (int i = static_cast<int>(audio_queue.size()) - 1; i >= 0; i--) {
		auto& sound_entry = audio_queue[i];
		if (sound_entry.struct_sfsound.getStatus() != sf::Sound::Status::Playing && !sound_entry.started) {
			//NEED SOME LOGIC HERE FOR DIFFERENT SOUND TYPES - DO WE ALWAYS PLAY THE SAMPLES?
			manageQueue(sound_entry);
			//sound_entry.struct_sfsound.play();
			//sound_entry.started = true;
		}

		if (sound_entry.struct_sfsound.getStatus() != sf::Sound::Status::Playing && sound_entry.started) {
			// Cache the pointer before erasing
			std::shared_ptr<Sound> finished_sound = sound_entry.struct_sound;

			//IF ITS SFX FIND IN POOL AND REMOVE
			if (finished_sound->getType() == Audiotypes::SFX) {
				auto it = std::find(sfx_pool.begin(), sfx_pool.end(), finished_sound);
				if (it != sfx_pool.end()) {
					sfx_pool.erase(it);
				}
			}
			sound_entry.started = false;
			std::cout << "ERASED AUDIO FROM QUEUE" << std::endl;
			audio_queue.erase(audio_queue.begin() + i);
		}
	}
}

void Audio::manageQueue(SoundStruct& sound_entry)
{

	//LOGIC HERE
	if (sound_entry.struct_sound->getType() != Audiotypes::SFX) {
		switch (sound_entry.struct_sound->getType()) {
		case Audiotypes::ENVIRO:
		{
			//SHOULD ALL PLAY AT THE SAME TIME QUEUE SHOULD PREVENT DUPLICATION OF SOUND OBJECTS
			sound_entry.struct_sfsound.play();
			sound_entry.started = true;

			break;
		}
		case Audiotypes::NPC:
		{

			break;
		}
		case Audiotypes::PLAYER:
		{
			//CHECK TO SEE IF PLAYER AUDIO ALREADY PLAYING AND IF NOT PLAY
			if (!isPlaying(sound_entry.struct_sound->getType())) {
				sound_entry.struct_sfsound.play();
				sound_entry.started = true;
			}
			break;
		}
		case Audiotypes::NARRATIVE:
		{
			break;
		}
		}
	}
	else {
		sound_entry.struct_sfsound.play();
		sound_entry.started = true;
	}

}

void Audio::queueSound(std::shared_ptr<Sound> sound)
{
	//THIS FUNCTION QUEUES THE SOUNDS IF THERE IS VALID SPACE FOR THAT SOUND TYPE
	//THIS QUEUE PREVENTS EXCESS AUDIO QUEUE
	// TO DO - DECIDE WHAT EACH SOUNDS PRIORITY IS AND HOW MANY SOUNDS SHOULD BE ABLE TO BE QUEUED OF EACH TYPE
	std::cout << "Attempting to queue sound..." << std::endl;
	switch (sound->getType()) {
	case Audiotypes::SFX:
	{
		//NEED TO HAVE AN SFX BUFFER VECTOR? STORES THE BUFFERS? OR STRUCT AND STORE PAIRS? OR DO WE KEEP 10 EMPTY BUFFERS AND ASSIGN THE FILE...
		//IF SFX IS QUEUED - DUPLICATE THE BUFFER AND LOAD SOUND
		//HAVE 10 BUFFERS HANDY - CHECK TO SEE HOW MANY CURRENTLY LOADED AND USE THE NEXT AVAILABLE BUFFER SPACE?
		if (addSFXtoPool(sound->getPath())) {
			//ADDED TO POOL
			sf::Sound tempsound(sound->getBuffer());
			SoundStruct temp{ std::move(tempsound), sfx_pool[sfx_pool.size() - 1], 0 };
			audio_queue.push_back(temp);
		}
		else {
			//POOL IS FULL
			//COULD CLEAR ALL REMAINING SFX AT THIS POINT?
		}
		std::cout << "Queuing SFX" << std::endl;
		break;
	}
	case Audiotypes::ENVIRO:
	{
		if (isQueued(sound)) { std::cout << "ALREADY IN ENVIRO QUEUE" << std::endl; }
		else {
			std::cout << "Queuing ENVIRO" << std::endl;
			//vec_audio_queue.push_back(sound);

			sf::Sound tempsound(sound->getBuffer());
			SoundStruct temp{ std::move(tempsound), sound };
			audio_queue.push_back(temp);
		}
		break;
	}
	case Audiotypes::NPC:
	{
		//ONLY QUEUE A MAXIMUM OF 5 AUDIOS FROM THIS TYPE

		break;
	}
	case Audiotypes::PLAYER:
	{
		if (numQueued(Audiotypes::PLAYER) > 3) {
			std::cout << "num in queue = " << numQueued(Audiotypes::PLAYER) << std::endl;
			std::cout << "ALREADY IN PLAYER QUEUE" << std::endl; 
		}
		else {
			std::cout << "Queuing PLAYER" << std::endl;
			//vec_audio_queue.push_back(sound);
			std::cout << "num in queue = " << numQueued(Audiotypes::PLAYER) << std::endl;

			sf::Sound tempsound(sound->getBuffer());
			SoundStruct test{ std::move(tempsound), sound };
			audio_queue.push_back(test);
		}
		break;
	}
	case Audiotypes::NARRATIVE:
	{
		break;
	}
	}
}

bool Audio::isQueued(std::shared_ptr<Sound> sound) {
	return std::any_of(audio_queue.begin(), audio_queue.end(),
		[&](const SoundStruct& entry) {
			return entry.struct_sound == sound;
		});
}

bool Audio::isQueued(Audiotypes type) {
	return std::any_of(audio_queue.begin(), audio_queue.end(),
		[&](const SoundStruct& entry) {
			return entry.struct_sound && entry.struct_sound->getType() == type;
		});
}

int Audio::numQueued(std::shared_ptr<Sound> sound)
{
	//COUNT THE NUMBER OF QUEUED SOUNDS BY SOUND
	return std::count_if(audio_queue.begin(), audio_queue.end(),
		[&sound](const SoundStruct& entry) {
			return entry.struct_sound == sound;
		});
}

int Audio::numQueued(Audiotypes type)
{
	//COUNT THE NUMBER OF QUEUED SOUNDS BY TYPE
	return std::count_if(audio_queue.begin(), audio_queue.end(),
		[&](const SoundStruct& entry) {
			return entry.struct_sound && entry.struct_sound->getType() == type;
		});
}

bool Audio::isPlaying(std::shared_ptr<Sound> sound) {
	return std::any_of(audio_queue.begin(), audio_queue.end(),
		[&](const SoundStruct& entry) {
			return entry.struct_sound == sound 
				&& entry.struct_sfsound.getStatus() == sf::Sound::Status::Playing;
		});
}

bool Audio::isPlaying(Audiotypes type) {
	return std::any_of(audio_queue.begin(), audio_queue.end(),
		[&](const SoundStruct& entry) {
			return entry.struct_sound 
				&& entry.struct_sound->getType() == type 
				&& entry.struct_sfsound.getStatus() == sf::Sound::Status::Playing;
		});
}

bool Audio::addSFXtoPool(std::string path)
{
	if (sfx_pool.size() < 10) {
		sfx_pool.push_back(std::make_shared<Sound>());
		sfx_pool[sfx_pool.size() - 1]->setType(Audiotypes::SFX);
		sfx_pool[sfx_pool.size() - 1]->loadBuffer(path);
		return true;
	}
	else {
		return false;
	}
}

int Audio::fadeVolumeIn(int& volume)
{
	if (volume < full_volume) { volume++; }
	return volume;
}

int Audio::fadeVolumeOut(int& volume)
{
	if (volume > quiet_volume) { volume--; }
	return volume;
}
