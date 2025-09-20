#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "../Enums.h"

class TypeCheck
{

public:
	TypeCheck();
	~TypeCheck();

	//GETTERS AND SETTERS
	void setPlayerInput(std::string string);
	std::string getPlayerInput();


	//FUNCTIONS

	void initDialogue();
	void initPlayerDialogue();
	void speak();
	void compareStrings();


private:

	std::vector<std::string> vec_dialogue;
	std::vector<std::string> vec_player_dialogue;

	std::string player_input;

	std::vector<std::string> vec_dialogue;
};