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
	//int random = rand() % vec_player_dialogue.size();
	//std::cout << vec_player_dialogue[random] << std::endl;

	if (!vec_challenge.empty()) {
		int random = rand() % vec_challenge.size();
		std::cout << vec_challenge[random] << std::endl;
	}
	else {
		std::cout << "empty" << std::endl;
	}
}

void TypeCheck::typingChallenge()
{
	//pulls a random dialogue and prints it for replication
	
	int random = rand() % vec_player_dialogue.size();

	//stores in array

	std::string line = vec_player_dialogue[random];

	std::string delimiter = " ";
	size_t pos = 0;
	std::string token;

	//BREAK DOWN BY DELIMITER INTO PARTS ARRAY
	while ((pos = line.find(delimiter)) != std::string::npos) {
		token = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());
		vec_challenge.emplace_back(token);
	}
	// FINAL PART AFTER DELIMITER
	vec_challenge.emplace_back(line);

	//std::cout << "challenge : " << vec_challenge[2] << std::endl;
}

void TypeCheck::compareStrings()
{
	
	//when typing as you add the chars to a string when you hit space it needs to check the word against your entry, and if good change word green if bad change word red,
	//on a count down to force fast typing
	//load the phrase into array word by word, reverse the array, and work from the back popping off each element until array = empty
	//each green hit = point,
	if (player_input == "") {
		if (strike) {
			//no input twice void next word
			std::cout << "strike 2" << std::endl;
		}
		else {
			//no input strike 1 void next word
			strike = true;
			std::cout << "strike 1" << std::endl;
		}
	}
	else {
		//break down each word and check each character against the next word in the array
		strike = false;
		std::cout << "array check" << std::endl;
		if (!vec_challenge.empty()) {
			std::string word = vec_challenge[0];
			if (word.size() == player_input.size())
			{
				std::cout << "SAME SIZE" << word.size() << " " << player_input.size() << std::endl;
				int i = 0;
				while (i < player_input.size() && word_fail == false) {
					if (word[i] != player_input[i]) {
						std::cout << "FAIL" << std::endl;
						word_fail = true;
					}
					i++;
				}	
				if (word_fail) {
					//THE WORD IS STUCK OUT RED
				}
				else {
					//WORD IS GREEN
					//POINTS AWARDED
				}
			}
			else {
				std::cout << "NOT SAME SIZE" << word.size() << " " << player_input.size() << std::endl;
				//THE WORD IS STUCK OUT RED
				vec_challenge.erase(vec_challenge.begin(), vec_challenge.begin());
			}
		}
		else
		{
			std::cout << "CHALLENGE IS OVER" << std::endl;
			//SUM OF ALL POINTS
		}
	}

}

void TypeCheck::recordPLayerInput(std::string text_entered)
{
	//TAKES THE STRING AND ADDS TO IT FOR TEXT ENTERED EVENT - NEED TO ACTIVATE THIS IN CERTAIN GAME STATE
	if (text_entered == " ") {
		compareStrings();
		player_input = "";
	}
	else {
		player_input += text_entered;
	}
	std::cout << "player input: " << player_input << std::endl;
}


