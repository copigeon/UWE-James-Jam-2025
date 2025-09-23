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
	std::vector<sf::Text> getVecChallengeText();


	//FUNCTIONS

	void initDialogue();
	void initPlayerDialogue();
	void speak();
	void typingChallenge();
	void compareStrings();
	void recordPLayerInput(std::string text_entered);

private:

	std::vector<std::string> vec_dialogue;
	std::vector<std::string> vec_player_dialogue;

	std::string player_input;

	bool strike = false;
	bool word_fail = false;

	std::vector<std::string> vec_challenge;
	std::vector<sf::Text> vec_challenge_text;

	sf::Font font;
	
	//MUST ADD TEXT CLASS AND FONT CLASS

};