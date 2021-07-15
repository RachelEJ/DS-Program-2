/*
Student Name: Rachel Jordan
Student NetID: rej168
Compiler Used: Visual Studio
Program Description: A program that can create and solve puzzles based on the SET puzzle
*/


#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "card.h"
#include "puzzle.h"
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::istream;
using std::ifstream;
using std::stringstream;
using std::left;
using std::setw;
using std::setfill;
using std::to_string;
using std::transform;

// checks if the string is valid (has 4 caracters, in proper format, etc)
bool checkString(string check)
{

	int valid = 0;
	if (check.size() == 4)
	{
		valid++;
		if (check[0] == '1')
		{
			valid++;
		}
		else if (check[0] == '2')
		{
			valid++;
		}
		else if (check[0] == '3')
		{
			valid++;
		}
		if (check[1] == 'r')
		{
			valid++;
		}
		else if (check[1] == 'g')
		{
			valid++;
		}
		else if (check[1] == 'p')
		{
			valid++;
		}
		if (check[2] == 'f')
		{
			valid++;
		}
		else if (check[2] == 'o')
		{
			valid++;
		}
		else if (check[2] == 's')
		{
			valid++;
		}
		if (check[3] == 'd')
		{
			valid++;
		}
		else if (check[3] == 'o')
		{
			valid++;
		}
		else if (check[3] == 's')
		{
			valid++;
		}
		if (valid == 5)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	else
	{
		return false;
	}
}

// tests 3 cards to see if they can form a set
bool testC(string cardT1, string cardT2, string cardT3)
{
	if ((cardT1[0] != cardT2[0] && cardT1[0] != cardT3[0] && cardT2[0] != cardT3[0]) || (cardT1[0] == cardT2[0] && cardT1[0] == cardT3[0] && cardT2[0] == cardT3[0]))
	{
		if ((cardT1[1] != cardT2[1] && cardT1[1] != cardT3[1] && cardT2[1] != cardT3[1]) || (cardT1[1] == cardT2[1] && cardT1[1] == cardT3[1] && cardT2[1] == cardT3[1]))
		{
			if ((cardT1[2] != cardT2[2] && cardT1[2] != cardT3[2] && cardT2[2] != cardT3[2]) || (cardT1[2] == cardT2[2] && cardT1[2] == cardT3[2] && cardT2[2] == cardT3[2]))
			{
				if ((cardT1[3] != cardT2[3] && cardT1[3] != cardT3[3] && cardT2[3] != cardT3[3]) || (cardT1[3] == cardT2[3] && cardT1[3] == cardT3[3] && cardT2[3] == cardT3[3]))
				{
					return true;
				}
			}
		}
	}
	return false;
}

// displays list of all puzzles
void display(vector<Puzzle*>puzzleList)
{
	cout << "The following puzzles are available to edit or solve" << endl << endl;
	if (puzzleList.size() == 0)
	{
		cout << "\t No puzzles found" << endl << endl;
	}
	else
	{
		for (int i = 0; i < puzzleList.size(); i++)
		{
			cout << puzzleList[i]->getNamePuzzle() << endl;
		}
	}
}

// searches if a puzzle exists or not
int searchPuzzle(const vector<Puzzle*>puzzleList, string key)
{
	int exist = 0;

	if (puzzleList.size() == 0)
	{
		return 0;
	}
	else
	{
		for (int i = 0; i < puzzleList.size(); i++)
		{
			if (puzzleList[i]->getNamePuzzle() == key)
			{
				exist++;
			}
		}
		if (exist == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	
}

// creates a new puzzle and adds it to the vector of all puzzles
bool createPuzzle(vector<Puzzle*>&puzzleList, string newPuzzle)
{
	// checks if the puzzle exists or not
	int preexist = searchPuzzle(puzzleList, newPuzzle);
	if (preexist == 0)
	{
		Puzzle* temp = new Puzzle(newPuzzle);
		puzzleList.push_back(temp);

		cout << "Successfully created the puzzle" << endl << endl;
		return true;
	}
	else
	{
		cout << "The puzzle " << newPuzzle << " already exists" << endl << endl;
		return false;
	}
}

// removes a puzzle from the vector of all puzzles
bool removePuzzle(vector<Puzzle*>& puzzleList, string remPuzzle)
{
	int find = searchPuzzle(puzzleList, remPuzzle);

	// Puzzle doesn't exist
	if (find == 0)
	{
		cout << "The puzzle " << remPuzzle << " does not exist." << endl << endl;
		return false;
	}

	// Removes a puzzle
	else
	{
		for (int i = 0; i < puzzleList.size(); i++)
		{
			if (puzzleList[i]->getNamePuzzle() == remPuzzle)
			{
				delete puzzleList[i];
				puzzleList.erase(puzzleList.begin() + i);
				break;
			}
		}
		cout << "Successfully removed puzzle " << remPuzzle << endl << endl;
		return true;
	}
}

// my monster of a function to take 2 cards as input, analyze, and replicate the pattern for the 3rd card
bool solve2(string cardT1, string cardT2, int numList[], string colorList[], string shadeList[], string shapeList[])
{
	const char separator = ' ';
	const int numWidth = 3;
	const int colorWidth = 8;
	const int shadeWidth = 9;
	const int shapeWidth = 12;

	// in case the 2 inputs are exactly the same
	if ((cardT1[0] == cardT2[0]) && (cardT1[1] == cardT2[1]) && (cardT1[2] == cardT2[2]) && (cardT1[3] == cardT2[3]))
	{
		cout << "Those two cards are exactly the same" << endl;
	}
	else
	{
		// tests the strings of the 2 cards by every corresponding character;
		// it also uses a vector of strings to test for valid input
		if (cardT1[0] != cardT2[0]) {
			if (cardT1[1] != cardT2[1]) {
				if (cardT1[2] != cardT2[2]) {
					if (cardT1[3] != cardT2[3]) {
						cout << "The last card in the set is ";
						for (int i = 0; i < 3; i++)
						{
							int tm = numList[i];
							char tmpNum = '0' + tm;
							if ((tmpNum != cardT1[0]) && (tmpNum != cardT2[0]))
							{
								cout << left << setw(numWidth) << setfill(separator) << numList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((colorList[i][0] != cardT1[1]) && (colorList[i][0] != cardT2[1]))
							{
								cout << left << setw(colorWidth) << setfill(separator) << colorList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((shadeList[i][0] != cardT1[2]) && (shadeList[i][0] != cardT2[2]))
							{
								cout << left << setw(shadeWidth) << setfill(separator) << shadeList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((shapeList[i][0] != cardT1[3]) && (shapeList[i][0] != cardT2[3]))
							{
								cout << left << setw(shapeWidth) << setfill(separator) << shapeList[i];
							}
						}
						return true;
					}
					else if (cardT1[3] == cardT2[3]) {
						cout << "The last card in the set is ";
						for (int i = 0; i < 3; i++)
						{
							int tm = numList[i];
							char tmpNum = '0' + tm;
							if ((tmpNum != cardT1[0]) && (tmpNum != cardT2[0]))
							{
								cout << left << setw(numWidth) << setfill(separator) << numList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((colorList[i][0] != cardT1[1]) && (colorList[i][0] != cardT2[1]))
							{
								cout << left << setw(colorWidth) << setfill(separator) << colorList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((shadeList[i][0] != cardT1[2]) && (shadeList[i][0] != cardT2[2]))
							{
								cout << left << setw(shadeWidth) << setfill(separator) << shadeList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (shapeList[i][0] == cardT1[3])
							{
								cout << left << setw(shapeWidth) << setfill(separator) << shapeList[i];
							}
						}
						return true;
					}
					else {
						return false;
					}
				}
				else if (cardT1[2] == cardT2[2]) {
					if (cardT1[3] != cardT2[3]) {
						cout << "The last card in the set is ";
						for (int i = 0; i < 3; i++)
						{
							int tm = numList[i];
							char tmpNum = '0' + tm;
							if ((tmpNum != cardT1[0]) && (tmpNum != cardT2[0]))
							{
								cout << left << setw(numWidth) << setfill(separator) << numList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((colorList[i][0] != cardT1[1]) && (colorList[i][0] != cardT2[1]))
							{
								cout << left << setw(colorWidth) << setfill(separator) << colorList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (shadeList[i][0] == cardT1[3])
							{
								cout << left << setw(shadeWidth) << setfill(separator) << shadeList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((shapeList[i][0] != cardT1[3]) && (shapeList[i][0] != cardT2[3]))
							{
								cout << left << setw(shapeWidth) << setfill(separator) << shapeList[i];
							}
						}
						return true;
					}
					else if (cardT1[3] == cardT2[3]) {
						cout << "The last card in the set is ";
						for (int i = 0; i < 3; i++)
						{
							int tm = numList[i];
							char tmpNum = '0' + tm;
							if ((tmpNum != cardT1[0]) && (tmpNum != cardT2[0]))
							{
								cout << left << setw(numWidth) << setfill(separator) << numList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((colorList[i][0] != cardT1[1]) && (colorList[i][0] != cardT2[1]))
							{
								cout << left << setw(colorWidth) << setfill(separator) << colorList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (shadeList[i][0] == cardT1[2])
							{
								cout << left << setw(shadeWidth) << setfill(separator) << shadeList[i];
							}
						}

						for (int i = 0; i < 3; i++)
						{
							if (shapeList[i][0] == cardT1[3])
							{
								cout << left << setw(shapeWidth) << setfill(separator) << shapeList[i];
							}
						}
						return true;
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
			else if (cardT1[1] == cardT2[1]) {
				if (cardT1[2] != cardT2[2]) {
					if (cardT1[3] != cardT2[3]) {
						cout << "The last card in the set is ";
						for (int i = 0; i < 3; i++)
						{
							int tm = numList[i];
							char tmpNum = '0' + tm;
							if ((tmpNum != cardT1[0]) && (tmpNum != cardT2[0]))
							{
								cout << left << setw(numWidth) << setfill(separator) << numList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (colorList[i][0] == cardT1[1])
							{
								cout << left << setw(colorWidth) << setfill(separator) << colorList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((shadeList[i][0] != cardT1[2]) && (shadeList[i][0] != cardT2[2]))
							{
								cout << left << setw(shadeWidth) << setfill(separator) << shadeList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((shapeList[i][0] != cardT1[3]) && (shapeList[i][0] != cardT2[3]))
							{
								cout << left << setw(shapeWidth) << setfill(separator) << shapeList[i];
							}
						}
						return true;
					}
					else if (cardT1[3] == cardT2[3]) {
						cout << "The last card in the set is ";
						for (int i = 0; i < 3; i++)
						{
							int tm = numList[i];
							char tmpNum = '0' + tm;
							if ((tmpNum != cardT1[0]) && (tmpNum != cardT2[0]))
							{
								cout << left << setw(numWidth) << setfill(separator) << numList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (colorList[i][0] == cardT1[1])
							{
								cout << left << setw(colorWidth) << setfill(separator) << colorList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((shadeList[i][0] != cardT1[2]) && (shadeList[i][0] != cardT2[2]))
							{
								cout << left << setw(shadeWidth) << setfill(separator) << shadeList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (shapeList[i][0] == cardT1[3])
							{
								cout << left << setw(shapeWidth) << setfill(separator) << shapeList[i];
							}
						}
						return true;
					}
					else {
						return false;
					}
				}
				else if (cardT1[2] == cardT2[2]) {
					if (cardT1[3] != cardT2[3]) {
						cout << "The last card in the set is ";
						for (int i = 0; i < 3; i++)
						{
							int tm = numList[i];
							char tmpNum = '0' + tm;
							if ((tmpNum != cardT1[0]) && (tmpNum != cardT2[0]))
							{
								cout << left << setw(numWidth) << setfill(separator) << numList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (colorList[i][0] == cardT1[1])
							{
								cout << left << setw(colorWidth) << setfill(separator) << colorList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (shadeList[i][0] == cardT1[3])
							{
								cout << left << setw(shadeWidth) << setfill(separator) << shadeList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((shapeList[i][0] != cardT1[3]) && (shapeList[i][0] != cardT2[3]))
							{
								cout << left << setw(shapeWidth) << setfill(separator) << shapeList[i];
							}
						}
						return true;
					}
					else if (cardT1[3] == cardT2[3]) {
						cout << "The last card in the set is ";
						for (int i = 0; i < 3; i++)
						{
							int tm = numList[i];
							char tmpNum = '0' + tm;
							if ((tmpNum != cardT1[0]) && (tmpNum != cardT2[0]))
							{
								cout << left << setw(numWidth) << setfill(separator) << numList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (colorList[i][0] == cardT1[1])
							{
								cout << left << setw(colorWidth) << setfill(separator) << colorList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (shadeList[i][0] == cardT1[2])
							{
								cout << left << setw(shadeWidth) << setfill(separator) << shadeList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (shapeList[i][0] == cardT1[3])
							{
								cout << left << setw(shapeWidth) << setfill(separator) << shapeList[i];
							}
						}
						return true;
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else if (cardT1[0] == cardT2[0]) {
			if (cardT1[1] != cardT2[1]) {
				if (cardT1[2] != cardT2[2]) {
					if (cardT1[3] != cardT2[3]) {
						cout << "The last card in the set is ";
						for (int i = 0; i < 3; i++)
						{
							int tm = numList[i];
							char tmpNum = '0' + tm;
							if (tmpNum == cardT1[0])
							{
								cout << left << setw(numWidth) << setfill(separator) << numList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((colorList[i][0] != cardT1[1]) && (colorList[i][0] != cardT2[1]))
							{
								cout << left << setw(colorWidth) << setfill(separator) << colorList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((shadeList[i][0] != cardT1[2]) && (shadeList[i][0] != cardT2[2]))
							{
								cout << left << setw(shadeWidth) << setfill(separator) << shadeList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((shapeList[i][0] != cardT1[3]) && (shapeList[i][0] != cardT2[3]))
							{
								cout << left << setw(shapeWidth) << setfill(separator) << shapeList[i];
							}
						}
					}
					else if (cardT1[3] == cardT2[3]) {
						cout << "The last card in the set is ";
						for (int i = 0; i < 3; i++)
						{
							int tm = numList[i];
							char tmpNum = '0' + tm;
							if (tmpNum == cardT1[0])
							{
								cout << left << setw(numWidth) << setfill(separator) << numList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((colorList[i][0] != cardT1[1]) && (colorList[i][0] != cardT2[1]))
							{
								cout << left << setw(colorWidth) << setfill(separator) << colorList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((shadeList[i][0] != cardT1[2]) && (shadeList[i][0] != cardT2[2]))
							{
								cout << left << setw(shadeWidth) << setfill(separator) << shadeList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (shapeList[i][0] == cardT1[3])
							{
								cout << left << setw(shapeWidth) << setfill(separator) << shapeList[i];
							}
						}
						return true;
					}
					else {
						return false;
					}
				}
				else if (cardT1[2] == cardT2[2]) {
					if (cardT1[3] != cardT2[3]) {
						cout << "The last card in the set is ";
						for (int i = 0; i < 3; i++)
						{
							int tm = numList[i];
							char tmpNum = '0' + tm;
							if (tmpNum == cardT1[0])
							{
								cout << left << setw(numWidth) << setfill(separator) << numList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((colorList[i][0] != cardT1[1]) && (colorList[i][0] != cardT2[1]))
							{
								cout << left << setw(colorWidth) << setfill(separator) << colorList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (shadeList[i][0] == cardT1[3])
							{
								cout << left << setw(shadeWidth) << setfill(separator) << shadeList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((shapeList[i][0] != cardT1[3]) && (shapeList[i][0] != cardT2[3]))
							{
								cout << left << setw(shapeWidth) << setfill(separator) << shapeList[i];
							}
						}
						return true;
					}
					else if (cardT1[3] == cardT2[3]) {
						cout << "The last card in the set is ";
						for (int i = 0; i < 3; i++)
						{
							int tm = numList[i];
							char tmpNum = '0' + tm;
							if (tmpNum == cardT1[0])
							{
								cout << left << setw(numWidth) << setfill(separator) << numList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((colorList[i][0] != cardT1[1]) && (colorList[i][0] != cardT2[1]))
							{
								cout << left << setw(colorWidth) << setfill(separator) << colorList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (shadeList[i][0] == cardT1[2])
							{
								cout << left << setw(shadeWidth) << setfill(separator) << shadeList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (shapeList[i][0] == cardT1[3])
							{
								cout << left << setw(shapeWidth) << setfill(separator) << shapeList[i];
							}
						}
						return true;
					}
				}
				else {
					return false;
				}
			}
			else if (cardT1[1] == cardT2[1]) {
				if (cardT1[2] != cardT2[2]) {
					if (cardT1[3] != cardT2[3]) {
						cout << "hello" << endl;
						cout << "The last card in the set is ";
						for (int i = 0; i < 3; i++)
						{
							int tm = numList[i];
							char tmpNum = '0' + tm;
							if (tmpNum == cardT1[0])
							{
								cout << left << setw(numWidth) << setfill(separator) << numList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (colorList[i][0] == cardT1[1])
							{
								cout << left << setw(colorWidth) << setfill(separator) << colorList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((shadeList[i][0] != cardT1[2]) && (shadeList[i][0] != cardT2[2]))
							{
								cout << left << setw(shadeWidth) << setfill(separator) << shadeList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((shapeList[i][0] != cardT1[3]) && (shapeList[i][0] != cardT2[3]))
							{
								cout << left << setw(shapeWidth) << setfill(separator) << shapeList[i];
							}
						}
						return true;
					}
					else if (cardT1[3] == cardT2[3]) {
						cout << "The last card in the set is ";
						for (int i = 0; i < 3; i++)
						{
							int tm = numList[i];
							char tmpNum = '0' + tm;
							if (tmpNum == cardT1[0])
							{
								cout << left << setw(numWidth) << setfill(separator) << numList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (colorList[i][0] == cardT1[1])
							{
								cout << left << setw(colorWidth) << setfill(separator) << colorList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((shadeList[i][0] != cardT1[2]) && (shadeList[i][0] != cardT2[2]))
							{
								cout << left << setw(shadeWidth) << setfill(separator) << shadeList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (shapeList[i][0] == cardT1[3])
							{
								cout << left << setw(shapeWidth) << setfill(separator) << shapeList[i];
							}
						}
						return true;
					}
					else {
						return false;
					}
				}
				else if (cardT1[2] == cardT2[2]) {
					if (cardT1[3] != cardT2[3]) {
						cout << "The last card in the set is ";
						for (int i = 0; i < 3; i++)
						{
							int tm = numList[i];
							char tmpNum = '0' + tm;
							if (tmpNum == cardT1[0])
							{
								cout << left << setw(numWidth) << setfill(separator) << numList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (colorList[i][0] == cardT1[1])
							{
								cout << left << setw(colorWidth) << setfill(separator) << colorList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (shadeList[i][0] == cardT1[3])
							{
								cout << left << setw(shadeWidth) << setfill(separator) << shadeList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if ((shapeList[i][0] != cardT1[3]) && (shapeList[i][0] != cardT2[3]))
							{
								cout << left << setw(shapeWidth) << setfill(separator) << shapeList[i];
							}
						}
						return true;
					}
					else if (cardT1[3] == cardT2[3]) {
						cout << "The last card in the set is ";
						for (int i = 0; i < 3; i++)
						{
							int tm = numList[i];
							char tmpNum = '0' + tm;
							if (tmpNum == cardT1[0])
							{
								cout << left << setw(numWidth) << setfill(separator) << numList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (colorList[i][0] == cardT1[1])
							{
								cout << left << setw(colorWidth) << setfill(separator) << colorList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (shadeList[i][0] == cardT1[3])
							{
								cout << left << setw(shadeWidth) << setfill(separator) << shadeList[i];
							}
						}
						for (int i = 0; i < 3; i++)
						{
							if (shapeList[i][0] == cardT1[3])
							{
								cout << left << setw(shapeWidth) << setfill(separator) << shapeList[i];
							}
						}
						return true;
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	return false;
}
// the whole thing runs in the same manner as counting to 15 in binary
// 0 represents != and 1 represents ==

/*
Used the transform function to convert all the strings in puzzle.txt to lowercase
Came from GeeksforGeeks
https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/
*/
// reads cards from .txt files with only card names
void readCards(istream& is, bool isFile, vector<Puzzle*>& puzzleList, string pName)
{
	string line;
	string card1;
	string card2;
	string card3;
	string card4;
	string arg1;
	int index = 0;
	for (int disp = 0; disp < puzzleList.size(); disp++)
	{
		if (puzzleList[disp]->getNamePuzzle() == pName)
		{
			index = disp;
		}
	}
	while (true)
	{
		// opens, reads, and processes the file as card inputs to add to a puzzle
		if (isFile && is.eof()) return;
		getline(is, line);
		stringstream ss(line);
		getline(ss, card1, ' ');
		if (card1.size() == 4)
		{
			// changes all characters to lowercase
			transform(card1.begin() + 1, card1.end(), card1.begin() + 1, ::tolower);
			if (checkString(card1) == 1)
			{
				// in case the puzzle already has a card of the same name
				if (puzzleList[index]->searchPuzzle(card1) == 1)
				{
					cout << pName << " already contains " << card1 << endl << endl;
				}
				else
				{
					// builds the string of each new card
					int num = 0;
					string color = "";
					string shade = "";
					string shape = "";
					if (card1[0] == '1')
					{
						num = 1;
					}
					else if (card1[0] == '2')
					{
						num = 2;
					}
					else if (card1[0] == '3')
					{
						num = 3;
					}
					if (card1[1] == 'r')
					{
						color = "red";
					}
					else if (card1[1] == 'g')
					{
						color = "green";
					}
					else if (card1[1] == 'p')
					{
						color = "purple";
					}
					if (card1[2] == 'f')
					{
						shade = "filled";
					}
					else if (card1[2] == 'o')
					{
						shade = "open";
					}
					else if (card1[2] == 's')
					{
						shade = "striped";
					}
					if (card1[3] == 'd')
					{
						shape = "diamond";
					}
					else if (card1[3] == 'o')
					{
						shape = "oval";
					}
					else if (card1[3] == 's')
					{
						shape = "squiggle";
					}
					puzzleList[index]->appendPuzzle(num, color, shade, shape);
					cout << "Succesfully added " << card1 << " to " << pName << endl << endl;
				}

			}
			else
			{
				cout << "That is not a valid card" << endl << endl;
			}
		}
		// starts the code for card 2
		getline(ss, card2, ' ');
		if (card2.size() == 4)
		{
			transform(card2.begin() + 1, card2.end(), card2.begin() + 1, ::tolower);
			if (checkString(card2) == 1)
			{
				if (puzzleList[index]->searchPuzzle(card2) == 1)
				{
					cout << pName << " already contains " << card2 << endl << endl;
				}
				else
				{
					int num = 0;
					string color = "";
					string shade = "";
					string shape = "";
					if (card2[0] == '1')
					{
						num = 1;
					}
					else if (card2[0] == '2')
					{
						num = 2;
					}
					else if (card2[0] == '3')
					{
						num = 3;
					}
					if (card2[1] == 'r')
					{
						color = "red";
					}
					else if (card2[1] == 'g')
					{
						color = "green";
					}
					else if (card2[1] == 'p')
					{
						color = "purple";
					}
					if (card2[2] == 'f')
					{
						shade = "filled";
					}
					else if (card2[2] == 'o')
					{
						shade = "open";
					}
					else if (card2[2] == 's')
					{
						shade = "striped";
					}
					if (card2[3] == 'd')
					{
						shape = "diamond";
					}
					else if (card2[3] == 'o')
					{
						shape = "oval";
					}
					else if (card2[3] == 's')
					{
						shape = "squiggle";
					}
					puzzleList[index]->appendPuzzle(num, color, shade, shape);
					cout << "Succesfully added " << card2 << " to " << pName << endl << endl;
				}

			}
			else
			{
				cout << "That is not a valid card" << endl << endl;
			}
		}
		// starts the code for card 3
		getline(ss, card3, ' ');
		if (card3.size() == 4)
		{
			transform(card3.begin() + 1, card3.end(), card3.begin() + 1, ::tolower);
			if (checkString(card3) == 1)
			{
				if (puzzleList[index]->searchPuzzle(card3) == 1)
				{
					cout << pName << " already contains " << card3 << endl << endl;
				}
				else
				{
					int num = 0;
					string color = "";
					string shade = "";
					string shape = "";
					if (card3[0] == '1')
					{
						num = 1;
					}
					else if (card3[0] == '2')
					{
						num = 2;
					}
					else if (card3[0] == '3')
					{
						num = 3;
					}
					if (card3[1] == 'r')
					{
						color = "red";
					}
					else if (card3[1] == 'g')
					{
						color = "green";
					}
					else if (card3[1] == 'p')
					{
						color = "purple";
					}
					if (card3[2] == 'f')
					{
						shade = "filled";
					}
					else if (card3[2] == 'o')
					{
						shade = "open";
					}
					else if (card3[2] == 's')
					{
						shade = "striped";
					}
					if (card3[3] == 'd')
					{
						shape = "diamond";
					}
					else if (card3[3] == 'o')
					{
						shape = "oval";
					}
					else if (card3[3] == 's')
					{
						shape = "squiggle";
					}
					puzzleList[index]->appendPuzzle(num, color, shade, shape);
					cout << "Succesfully added " << card3 << " to " << pName << endl << endl;
				}

			}
			else
			{
				cout << "That is not a valid card" << endl << endl;
			}
		}
		// starts the code for card 4
		getline(ss, card4);
		if (card4.size() == 4)
		{
			transform(card4.begin() + 1, card4.end(), card4.begin() + 1, ::tolower);
			if (checkString(card4) == 1)
			{
				if (puzzleList[index]->searchPuzzle(card4) == 1)
				{
					cout << pName << " already contains " << card4 << endl << endl;
				}
				else
				{
					int num = 0;
					string color = "";
					string shade = "";
					string shape = "";
					if (card4[0] == '1')
					{
						num = 1;
					}
					else if (card4[0] == '2')
					{
						num = 2;
					}
					else if (card4[0] == '3')
					{
						num = 3;
					}
					if (card4[1] == 'r')
					{
						color = "red";
					}
					else if (card4[1] == 'g')
					{
						color = "green";
					}
					else if (card4[1] == 'p')
					{
						color = "purple";
					}
					if (card4[2] == 'f')
					{
						shade = "filled";
					}
					else if (card4[2] == 'o')
					{
						shade = "open";
					}
					else if (card4[2] == 's')
					{
						shade = "striped";
					}
					if (card4[3] == 'd')
					{
						shape = "diamond";
					}
					else if (card4[3] == 'o')
					{
						shape = "oval";
					}
					else if (card4[3] == 's')
					{
						shape = "squiggle";
					}
					puzzleList[index]->appendPuzzle(num, color, shade, shape);
					cout << "Succesfully added " << card4 << " to " << pName << endl << endl;
				}

			}
			else
			{
				cout << "That is not a valid card" << endl << endl;
			}
		}
		
	}
}

// reads the lines of a file and processes them as commands
void readLines(istream& is, bool isFile, vector<Puzzle*>&puzzleList)
{
	// the correct values for the strings
	int numList[] = { 1,2,3 };
	string colorList[] = { "red", "green", "purple" };
	string shadeList[] = { "filled", "open", "striped" };
	string shapeList[] = { "diamond", "oval", "squiggle" };

	while (true)
	{
		// actually reads everything and processes it as commands
		string line;
		string cmd;
		string arg1;
		string arg2;
		string arg3;
		if (isFile && is.eof()) return;
		getline(is, line);	
		stringstream ss(line);
		getline(ss, cmd, ' ');
		cout << endl;

		// exits the program
		if (cmd == "exit") return;

		// load function
		if (cmd == "load")
		{
			ifstream inFile;
			getline(ss, arg1, ' ');

			// if only 1 argument, opens and reads file's contents as commands
			if (!getline(ss, arg2, ' '))
			{
				if (!getline(ss, arg3, ' '))
				{
					inFile.open(arg1);
					cout << "Attempting to open file..." << endl << endl;
					if (inFile.is_open())
					{
						readLines(inFile, true, puzzleList);
					}
					else
					{
						cout << "Failed to open the file" << endl;
					}
					inFile.close();
				}
			}

			// if 2 arguments, opens and reads file's contents as cards to add to a puzzle
			else
			{
				getline(ss, arg2, ' ');
				inFile.open(arg1);
				cout << "Attempting to open file..." << endl;
				if (inFile.is_open())
				{
					if (searchPuzzle(puzzleList, arg2) == 0)
					{
						createPuzzle(puzzleList, arg2);
					}
					readCards(inFile, true, puzzleList, arg2);
				}
				else
				{
					cout << "Failed to open the file" << endl;
				}
				inFile.close();
			}
		}

		// display function
		if (cmd == "display")
		{
			
			// no arguments inputted: displays list of puzzles
			if (!getline(ss, arg1, ' '))
			{
				display(puzzleList);
			}

			// 1 argument: displays contents of puzzle inputted
			else
			{
				getline(ss, arg1, ' ');
				// checks if the puzzle exists or not
				if (searchPuzzle(puzzleList, arg1) == 0)
				{
					cout << arg1 << " does not exist" << endl;
				}
				else
				{
					// gets index for where the inputted puzzle is located
					for (int disp = 0; disp < puzzleList.size(); disp++)
					{
						if (puzzleList[disp]->getNamePuzzle() == arg1)
						{
							cout << arg1 << " contains:" << endl;
							puzzleList[disp]->displayPuzzle();
						}
						else
						{
							if (disp == puzzleList.size() - 1)
							{
								cout << arg1 << " does not exist" << endl;
							}
						}
					}
				}
			}
		}

		// takes input for new puzzle name and calls createPuzzle()
		if (cmd == "new")
		{
			getline(ss, arg1, ' ');
			createPuzzle(puzzleList, arg1);
		}

		// remove function
		if (cmd == "remove")
		{
			getline(ss, arg1, ' ');

			// 1 argument: removes puzzle with inputted name
			if (!getline(ss, arg2, ' '))
			{
				removePuzzle(puzzleList, arg1);
			}

			// 2 arguments: removes card from puzzle
			else
			{
				getline(ss, arg2, ' ');
				if (searchPuzzle(puzzleList, arg2) == 1)
				{
					getline(ss, arg2);
					for (int disp = 0; disp < puzzleList.size(); disp++)
					{
						if (puzzleList[disp]->getNamePuzzle() == arg2)
						{
							if (puzzleList[disp]->removeCardPuzzle(arg1) == 1)
							{
								cout << arg1 << " successfully removed from " << puzzleList[disp]->getNamePuzzle() << endl;
							}
							else
							{
								cout << "Error while removing " << arg1 << " from " << puzzleList[disp]->getNamePuzzle() << endl;
							}
						}
					}
				}

				// in case the puzzle doesn't exist
				else
				{
					cout << arg2 << " does not exist as a puzzle" << endl;
				}
			}
			
		}

		// add function
		if (cmd == "add")
		{
			// reads in all inputs
			getline(ss, arg1, ' ');
			getline(ss, arg2, ' ');
			if (arg2 == "to")
			{
				getline(ss, arg3);

				// searches if puzzle exists
				if (searchPuzzle(puzzleList, arg3) == 1)
				{
					if (checkString(arg1) == 1)
					{
						int index = 0;
						for (int disp = 0; disp < puzzleList.size(); disp++)
						{
							if (puzzleList[disp]->getNamePuzzle() == arg3)
							{
								index = disp;
							}
						}

						// checks if card is already in puzzle
						if (puzzleList[index]->searchPuzzle(arg1) == 1)
						{
							cout << arg3 << " already contains " << arg1 << endl << endl;
						}

						// reads in and stores attributes for new card
						else
						{
							int num = 0;
							string color = "";
							string shade = "";
							string shape = "";
							if (arg1[0] == '1')
							{
								num = 1;
							}
							else if (arg1[0] == '2')
							{
								num = 2;
							}
							else if (arg1[0] == '3')
							{
								num = 3;
							}
							if (arg1[1] == 'r')
							{
								color = "red";
							}
							else if (arg1[1] == 'g')
							{
								color = "green";
							}
							else if (arg1[1] == 'p')
							{
								color = "purple";
							}
							if (arg1[2] == 'f')
							{
								shade = "filled";
							}
							else if (arg1[2] == 'o')
							{
								shade = "open";
							}
							else if (arg1[2] == 's')
							{
								shade = "striped";
							}
							if (arg1[3] == 'd')
							{
								shape = "diamond";
							}
							else if (arg1[3] == 'o')
							{
								shape = "oval";
							}
							else if (arg1[3] == 's')
							{
								shape = "squiggle";
							}

							// put the attributes into a card to add to the puzzle
							puzzleList[index]->appendPuzzle(num, color, shade, shape);
							cout << "Succesfully added " << arg1 << " to " << arg3 << endl << endl;
						}
					}

					// not a valid card
					else
					{
						cout << "That is not a valid card" << endl;
					}
				}

				// puzzle doesn't exist
				else {
					cout << arg3 << " does not exist as a puzzle" << endl;
				}
			}
		}

		// solve function
		if (cmd == "solve")
		{
			getline(ss, arg1, ' '); 

			// 1 argument: solves inputted puzzle
			if (!getline(ss, arg2, ' '))
			{
				if (searchPuzzle(puzzleList, arg1) == 1)
				{
					int index = 0;
					for (int disp = 0; disp < puzzleList.size(); disp++)
					{
						if (puzzleList[disp]->getNamePuzzle() == arg1)
						{
							index = disp;
						}
					}

					// in case the puzzle doesn't have enough cards to solve
					if (puzzleList[index]->getSizePuzzle() < 3)
					{
						cout << arg1 << " does not have enough card to solve" << endl;
					}
					else
					{

						// in case the puzzle doesn't have any solutions
						if (puzzleList[index]->solve() == 0)
						{
							cout << arg1 << " had no solutions" << endl;
						}
					}
				}
				else
				{
					cout << arg1 << " does not exist"<< endl;
				}
			}
			else
			{
				// converts all card strings to lowercase
				getline(ss, arg2, ' ');
				transform(arg1.begin() + 1, arg1.end(), arg1.begin() + 1, ::tolower);
				transform(arg2.begin() + 1, arg2.end(), arg2.begin() + 1, ::tolower);
				if (checkString(arg1) == 1)
				{
					if (checkString(arg2) == 1)
					{
						if (solve2(arg1, arg2, numList, colorList, shadeList, shapeList) == 0)
						{
							cout << "There is no card that can solve this set" << endl;
						}
						cout << endl;
					}
					else
					{
						cout << "That is not a valid card" << endl;
					}
				}
				else
				{
					cout << "That is not a valid card" << endl;
				}
			}
			

		}

		// test function
		if (cmd == "test")
		{
			// makes sure there's 3 inputs
			if (!getline(ss, arg1, ' ')) 
			{ 
				cout << "Test function needs 3 arguments" << endl; 
			}
			else
			{
				if (!getline(ss, arg2, ' ')) 
				{ 
					cout << "Test function needs 3 arguments" << endl; 
				}
				else
				{
					if (!getline(ss, arg3, ' ')) 
					{ 
						cout << "Test function needs 3 arguments" << endl; 
					}
					else
					{
						getline(ss, arg1, ' ');
						getline(ss, arg2, ' ');
						getline(ss, arg3, ' ');

						// converts all strings to lowercase
						try {
							transform(arg1.begin(), arg1.end(), arg1.begin(), ::tolower);
							transform(arg2.begin(), arg2.end(), arg2.begin(), ::tolower);
							transform(arg3.begin(), arg3.end(), arg3.begin(), ::tolower);				}
						catch (...)
						{
							cout << "That is not a valid card" << endl;
						}

						// makes sure all strings are valid
						if (checkString(arg1) == 1)
						{
							if (checkString(arg2) == 1)
							{
								if (checkString(arg3) == 1)
								{
									// makes sure no 2 cards are the same
									if (arg1 != arg2 && arg1 != arg3 && arg2 != arg3)
									{
										// calls testC with the strings
										if (testC(arg1, arg2, arg3) == 1)
										{
											cout << arg1 << ", " << arg2 << ", and " << arg3 << " form a set" << endl << endl;
										}
										else
										{

											cout << arg1 << ", " << arg2 << ", and " << arg3 << " do not form a set" << endl << endl;
										}
									}

									// the card contains duplicates
									else
									{
										cout << "These cards contain duplicates" << endl << endl;
									}
								}

								// not a valid card
								else
								{
									cout << "That is not a valid card" << endl << endl;
								}
							}
							else
							{
								cout << "That is not a valid card" << endl << endl;
							}
						}
						else
						{
							cout << "That is not a valid card" << endl << endl;
						}
					}
				}
			}
		}
	}
}

// my very empty int main
int main()
{
	vector<Puzzle*>puzzleList;

	readLines(cin, false, puzzleList);

	return 0;
}
