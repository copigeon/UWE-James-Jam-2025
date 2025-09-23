#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "TypeCheck.h"

TypeCheck::TypeCheck()
{
	if (!font.openFromFile("./Data/Fonts/zx-spectrum.ttf"))
	{
		// error...
		std::cout << "FONT DID NOT LOAD" << std::endl;
	}
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

std::vector<sf::Text> TypeCheck::getVecChallengeText()
{
	return vec_challenge_text;
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

	//CREATE THE TEXT ELEMENT

	//START HERE TOMORROW THIS IS THE LOOP THAT BE BROKEN

	sf::Text temp_text(font);
	temp_text.setCharacterSize(15);

	//BREAK DOWN BY DELIMITER INTO PARTS ARRAY
	while ((pos = line.find(delimiter)) != std::string::npos) {
		token = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());
		vec_challenge.emplace_back(token);

		temp_text.setString(token);
		vec_challenge_text.push_back(temp_text);
	}

	vec_challenge_text[0].setPosition(sf::Vector2f(100,50));

		// FINAL PART AFTER DELIMITER
		vec_challenge.emplace_back(line);
		temp_text.setString(line);
		vec_challenge_text.push_back(temp_text);

		int i = 1;
		while (i < vec_challenge_text.size()) {
			{
				vec_challenge_text[i].setPosition(sf::Vector2f((vec_challenge_text[i-1].getPosition().x + (vec_challenge_text[i-1].getGlobalBounds().size.x+20)), vec_challenge_text[i - 1].getPosition().y));
				i++;
			}
		}

	//std::cout << "challenge : " << vec_challenge[2] << std::endl;
}

void TypeCheck::compareStrings()
{

	//TRIGGER ON SPACE INPUT
	if (player_input == "" || player_input == "\r") {
		int word_count = vec_challenge_text.size() - vec_challenge.size();
		if (strike) {
			//no input twice void next word
			std::cout << "strike 2" << std::endl;
			vec_challenge_text[word_count].setFillColor(sf::Color::Red);
			vec_challenge.erase(vec_challenge.begin(), vec_challenge.begin() + 1);
			strike = false;
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
			int word_count = vec_challenge_text.size() - vec_challenge.size();
			std::string word = vec_challenge[0];
			if (word.size() == player_input.size())
			{
				std::cout << "word first letter is: " << word[0] << std::endl;
				std::cout << "SAME SIZE word is:" << word.size() << " player input is: " << player_input.size() << std::endl;
				int i = 0;
				while (i < player_input.size() && word_fail == false) {
					std::cout << "word letter is: " << word[i] << " and player letter is: " << player_input[i] << std::endl;
					if (word[i] != player_input[i]) {
						std::cout << "FAIL" << std::endl;
						word_fail = true;
						std::cout << "WORD FAIL TRUE" << std::endl;
					}
					i++;
				}
				if (word_fail) {
					//THE WORD IS STUCK OUT RED
					vec_challenge_text[word_count].setFillColor(sf::Color::Red);
					word_fail = false;
					vec_challenge.erase(vec_challenge.begin(), vec_challenge.begin()+1);
					std::cout << vec_challenge.size() << std::endl;
					if (vec_challenge.empty()) {
						std::cout << "CHALLENGE IS OVER" << std::endl;
					}
				}
				else {
					//WORD IS GREEN
					vec_challenge_text[word_count].setFillColor(sf::Color::Green);
					word_fail = false;
					vec_challenge.erase(vec_challenge.begin(), vec_challenge.begin()+1);
					std::cout << vec_challenge.size() << std::endl;
					if (vec_challenge.empty()) {
						std::cout << "CHALLENGE IS OVER" << std::endl;
					}
					//POINTS AWARDED
				}
			}
			else {
				std::cout << "word first letter is: " << word[0] << std::endl;
				std::cout << "NOT SAME SIZE word is: " << word.size() << " player input is: " << player_input.size() << std::endl;
				//THE WORD IS STUCK OUT RED
				vec_challenge_text[word_count].setFillColor(sf::Color::Red);
				vec_challenge.erase(vec_challenge.begin(), vec_challenge.begin()+1);
				std::cout << vec_challenge.size() << std::endl;
				if (vec_challenge.empty()) {
					std::cout << "CHALLENGE IS OVER" << std::endl;
				}
			}
		}
		else
		{
			std::cout << vec_challenge.size() << std::endl;
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


