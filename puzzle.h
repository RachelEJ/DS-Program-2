/*
Student Name: Rachel Jordan
Student NetID: rej168
Compiler Used: Visual Studio
Program Description: A program that can create and solve puzzles based on the SET puzzle
*/

#pragma once
#include <string>
#include "card.h"

using std::string;

class Puzzle
{
private:
	// Puzzle data
	int sizePuzzle;
	string namePuzzle;
	Card* head;
	Card* tail;

public:
	// basics
	Puzzle();
	Puzzle(string namePuzzle);
	~Puzzle();

	//getters
	int getSizePuzzle();
	string getNamePuzzle();

	// setters
	void setSizePuzzle(int sizePuzzle);
	void setNamePuzzle(string namePuzzle);

	// regular functions
	void displayPuzzle();
	void appendPuzzle(int number, string color, string shading, string shape);
	bool searchPuzzle(string key);
	bool removeCardPuzzle(string key);
	bool solve();
	bool test(string CT1, string CT2, string CT3);
};