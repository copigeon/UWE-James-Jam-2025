#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "TypeCheck.h"

TypeCheck::TypeCheck()
{

}

TypeCheck::~TypeCheck()
{

}

void TypeCheck::setPlayerInput(std::string string)
{
	player_input = string;
}

std::string TypeCheck::getPlayerInput()
{
	return player_input;
}

void TypeCheck::initDialogue()
{
	//READ IN THE INIT SOUNDS TEXT FILE
	std::ifstream file("./Data/Dialogue/dialogue.txt");
	std::string line;

	if (file.is_open()) {
		while (getline(file, line)) {
			std::cout << line << std::endl;
			vec_dialogue.emplace_back(line);
		}
		file.close();
	}
	else {
		std::cerr << "Unable to open file!" << std::endl;
	}
}

void TypeCheck::initPlayerDialogue()
{
	//READ IN THE INIT SOUNDS TEXT FILE
	std::ifstream file("./Data/Dialogue/dialogue_player.txt");
	std::string line;

	if (file.is_open()) {
		while (getline(file, line)) {
			std::cout << line << std::endl;
			vec_player_dialogue.emplace_back(line);
		}
		file.close();
	}
	else {
		std::cerr << "Unable to open file!" << std::endl;
	}
}

void TypeCheck::speak()
{
	//get a random dialogue
	int random = rand() % vec_player_dialogue.size();



	//std::cout << vec_player_dialogue[random] << std::endl;
}

void TypeCheck::compareStrings()
{
	//when typing as you add the chars to a string when you hit space it needs to check the word against your entry, and if good change word green if bad change word red,
	//on a count down to force fast typing
	//load the phrase into array word by word, reverse the array, and work from the back popping off each element until array = empty
	//each green hit = point,


}


