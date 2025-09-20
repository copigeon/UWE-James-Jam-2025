#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Sound.h"
#include "../Structs.h"
#include "../Enums.h"

class Audio
{
public:
	Audio();
	~Audio();

	//INIT FUNCTION FOR SOUNDS
	void initSounds();
	Audiotypes strtoType(std::string& str);

	//GETTERS AND SETTERS
	std::map<std::string, std::shared_ptr<Sound>>& getSounds(); //NO SETTER AS ONLY USED PRIVATELY DURING INIT

	//RUN EVERY LOOP
	void playSounds();
	void manageQueue(SoundStruct& sound_struct);
	
	//FUNCTION CALLS
	void queueSound(std::shared_ptr<Sound> sound);
	bool isQueued(std::shared_ptr<Sound> sound);
	bool isQueued(Audiotypes type);
	int numQueued(std::shared_ptr<Sound> sound);
	int numQueued(Audiotypes type);
	bool isPlaying(std::shared_ptr<Sound> sound);
	bool isPlaying(Audiotypes type);
	bool addSFXtoPool(std::string path);
	int fadeVolumeIn(int& volume);
	int fadeVolumeOut(int& volume);

	//std::vector<SoundStruct> audio_queue;

private:
	std::map<std::string, std::shared_ptr<Sound>> map_sounds;
	std::vector<std::shared_ptr<Sound>> sfx_pool;

	std::vector<SoundStruct> audio_queue;

	int volume = 50;
	int full_volume = 50;
	int quiet_volume = 10;

	int vol_narrative = 30;
	int vol_sfx = 30;
	int vol_player = 30;
	int vol_npc = 30;
	int vol_enviro = 30;
};
