/*
Student Name: Rachel Jordan
Student NetID: rej168
Compiler Used: Visual Studio
Program Description: A program that can create and solve puzzles based on the SET puzzle
*/

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include "puzzle.h"
#include "card.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::left;
using std::setw;
using std::setfill;
using std::to_string;

// puzzle constructor
Puzzle::Puzzle()
{
	sizePuzzle = 0;
	namePuzzle = "";
	head = nullptr;
}

// puzzle constructor with  namePuzz
Puzzle::Puzzle(string namePuzzle)
{
	sizePuzzle = 0;
	head = nullptr;
	this->namePuzzle = namePuzzle;
}

//Based on the deconstructor in the lecture notes
Puzzle::~Puzzle()
{
	Card* temp = head;

	while (temp != nullptr)
	{
		head = head->next;
		delete temp;
		temp = head;
	}
}

// getters
int Puzzle::getSizePuzzle()
{
	return sizePuzzle;
}
string Puzzle::getNamePuzzle()
{
	return namePuzzle;
}

// setters
void Puzzle::setSizePuzzle(int sizePuzzle)
{
	this->sizePuzzle = sizePuzzle;
}
void Puzzle::setNamePuzzle(string namePuzzle)
{
	this->namePuzzle = namePuzzle;
}

// makes new card with passed values and adds it to the puzzle
void Puzzle::appendPuzzle(int number, string color, string shading, string shape)
{
	Card* tmp = new Card(number, color, shading, shape);

	if (head == nullptr)
	{
		head = tmp;
	}
	else
	{
		tail->next = tmp;
	}
	tail = tmp;
	sizePuzzle++;
}

/*
Learned how to do the int to char conversion with this StackOverflow post
https://stackoverflow.com/questions/4629050/convert-an-int-to-ascii-character
I use this code in a few other places too
*/
// searches a puzzle for a certain value
bool Puzzle::searchPuzzle(string key)
{
	
	Card* tmp = head;
	
	while (tmp != nullptr)
	{
		int tm = tmp->number;
		char tmpNum = '0' + tm;
		if (key[0] == tmpNum)
		{
			if (key[1] == tmp->color[0])
			{
				if (key[2] == tmp->shading[0])
				{	
					if (key[3] == tmp->shape[0])
					{
						return true;
					}
				}
			}
		}
		tmp = tmp->next;
	}
	return false;
}

// removes card from a puzzle
bool Puzzle::removeCardPuzzle(string key)
{
	Card* tmp = head;
	Card* prev = nullptr;
	while (tmp != nullptr) {
		int tm = tmp->number;
		char tmpNum = '0' + tm;
	
		if (key[0] == tmpNum)
		{
			if (key[1] == tmp->color[0])
			{
				if (key[2] == tmp->shading[0])
				{
					if (key[3] == tmp->shape[0])
					{
						if (tmp == head)
						{
							head = tmp->next;
						}
						else
						{
							prev->next = tmp->next;
						}

						if (tmp == tail)
						{
							tail = prev;
						}

						delete tmp;
						sizePuzzle--;
						return true;
					}
				}
			}
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return false;
}


// Inspired by post from StackOverflow 
// https://stackoverflow.com/questions/14765155/how-can-i-easily-format-my-data-table-in-c
// displays contents of a specific puzzle
void Puzzle::displayPuzzle()
{
	Card* tmp = head;
	if (head == nullptr)
	{
		cout << "This puzzle is empty. Please try again.";
	}
	else
	{
		int cardCount = 1;
		const char separator = ' ';
		const int numWidth = 3;
		const int colorWidth = 8;
		const int shadeWidth = 9;
		const int shapeWidth = 12;

		while (tmp != nullptr)
		{
			cout << left << setw(numWidth) << setfill(separator) << tmp->number;
			cout << left << setw(colorWidth) << setfill(separator) << tmp->color;
			cout << left << setw(shadeWidth) << setfill(separator) << tmp->shading;
			cout << left << setw(shapeWidth) << setfill(separator) << tmp->shape;
			tmp = tmp->next;
			if ((cardCount % 4) == 0)
			{
				cout << endl << endl;
			}
			cardCount++;
		}
	}
	cout << endl;
}

// tests if the 3 cards can make a set
bool Puzzle::test(string cardT1, string cardT2, string cardT3)
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

/*
Learned how to append to strings with this site
http://www.cplusplus.com/reference/string/string/append/

Learned the while loop format from Mr. Knight
*/
// another monster function; takes 3 cards and finds all solutions without duplicates
bool Puzzle::solve()
{	
	int solCount = 0;
	const char separator = ' ';
	const int numWidth = 3;
	const int colorWidth = 8;
	const int shadeWidth = 9;
	const int shapeWidth = 12;
	vector<vector<string>>solutions;
	Card* tmp1 = head;
	Card* tmp2 = nullptr;
	Card* tmp3 = nullptr;
	cout << "Solutions to " << namePuzzle << ":" << endl;
	// loop while 1st pointer isn't nullptr
	while (tmp1 != nullptr)
	{
		// creates a string for the 1st pointer
		string test1 = "";
		if (tmp1->number == 1)
		{
			test1.append("1");
		}
		else if (tmp1->number == 2)
		{
			test1.append("2");
		}
		else if (tmp1->number == 3)
		{
			test1.append("3");
		}
		if (tmp1->color[0] == 'r')
		{
			test1.append("r");
		}
		else if (tmp1->color[0] == 'g')
		{
			test1.append("g");
		}
		else if (tmp1->color[0] == 'p')
		{
			test1.append("p");
		}
		if (tmp1->shading[0] == 'f')
		{
			test1.append("f");
		}
		else if (tmp1->shading[0] == 'o')
		{
			test1.append("o");
		}
		else if (tmp1->shading[0] == 's')
		{
			test1.append("s");
		}
		if (tmp1->shape[0] == 'd')
		{
			test1.append("d");
		}
		else if (tmp1->shape[0] == 'o')
		{
			test1.append("o");
		}
		else if (tmp1->shape[0] == 's')
		{
			test1.append("s");
		}
		tmp2 = tmp1->next;

		// loop for 2nd pointer
		while (tmp2 != nullptr)
		{
			// 2nd pointer string
			string test2 = "";
			if (tmp2->number == 1)
			{
				test2.append("1");
			}
			else if (tmp2->number == 2)
			{
				test2.append("2");
			}
			else if (tmp2->number == 3)
			{
				test2.append("3");
			}
			if (tmp2->color[0] == 'r')
			{
				test2.append("r");
			}
			else if (tmp2->color[0] == 'g')
			{
				test2.append("g");
			}
			else if (tmp2->color[0] == 'p')
			{
				test2.append("p");
			}
			if (tmp2->shading[0] == 'f')
			{
				test2.append("f");
			}
			else if (tmp2->shading[0] == 'o')
			{
				test2.append("o");
			}
			else if (tmp2->shading[0] == 's')
			{
				test2.append("s");
			}
			if (tmp2->shape[0] == 'd')
			{
				test2.append("d");
			}
			else if (tmp2->shape[0] == 'o')
			{
				test2.append("o");
			}
			else if (tmp2->shape[0] == 's')
			{
				test2.append("s");
			}
			tmp3 = tmp2->next;

			// loop for 3rd pointer
			while (tmp3 != nullptr)
			{
				// 3rd pointer string
				string test3 = "";
				if (tmp3->number == 1)
				{
					test3.append("1");
				}
				else if (tmp3->number == 2)
				{
					test3.append("2");
				}
				else if (tmp3->number == 3)
				{
					test3.append("3");
				}
				if (tmp3->color[0] == 'r')
				{
					test3.append("r");
				}
				else if (tmp3->color[0] == 'g')
				{
					test3.append("g");
				}
				else if (tmp3->color[0] == 'p')
				{
					test3.append("p");
				}
				if (tmp3->shading[0] == 'f')
				{
					test3.append("f");
				}
				else if (tmp3->shading[0] == 'o')
				{
					test3.append("o");
				}
				else if (tmp3->shading[0] == 's')
				{
					test3.append("s");
				}
				if (tmp3->shape[0] == 'd')
				{
					test3.append("d");
				}
				else if (tmp3->shape[0] == 'o')
				{
					test3.append("o");
				}
				else if (tmp3->shape[0] == 's')
				{
					test3.append("s");
				}

				// tests the strings
				int testT3 = test(test1, test2, test3);
				if (testT3 == 1)
				{
					// adds the strings to set vector
					vector<string>set;
					set.push_back(test1);
					set.push_back(test2);
					set.push_back(test3);

					// adds set to solution vector
					solutions.push_back(set);
					solCount++;
					// prints out the solution
						if (set[0][0] == '1')
						{
							cout << left << setw(numWidth) << setfill(separator) << "1";
						}
						else if (set[0][0] == '2')
						{
							cout << left << setw(numWidth) << setfill(separator) << "2";
						}
						else if (set[0][0] == '3')
						{
							cout << left << setw(numWidth) << setfill(separator) << "3";
						}
						if (set[0][1] == 'r')
						{
							cout << left << setw(colorWidth) << setfill(separator) << "red";
						}
						else if (set[0][1] == 'g')
						{
							cout << left << setw(colorWidth) << setfill(separator) << "green";
						}
						else if (set[0][1] == 'p')
						{
							cout << left << setw(colorWidth) << setfill(separator) << "purple";
						}
						if (set[0][2] == 'f')
						{
							cout << left << setw(shadeWidth) << setfill(separator) << "filled";
						}
						else if (set[0][2] == 'o')
						{
							cout << left << setw(shadeWidth) << setfill(separator) << "open";
						}
						else if (set[0][2] == 's')
						{
							cout << left << setw(shadeWidth) << setfill(separator) << "striped";
						}
						if (set[0][3] == 'd')
						{
							cout << left << setw(shapeWidth) << setfill(separator) << "diamond";
						}
						else if (set[0][3] == 'o')
						{
							cout << left << setw(shapeWidth) << setfill(separator) << "oval";
						}
						else if (set[0][3] == 's')
						{
							cout << left << setw(shapeWidth) << setfill(separator) << "squiggle";
						}

						if (set[1][0] == '1')
						{
							cout << left << setw(numWidth) << setfill(separator) << "1";
						}
						else if (set[1][0] == '2')
						{
							cout << left << setw(numWidth) << setfill(separator) << "2";
						}
						else if (set[1][0] == '3')
						{
							cout << left << setw(numWidth) << setfill(separator) << "3";
						}
						if (set[1][1] == 'r')
						{
							cout << left << setw(colorWidth) << setfill(separator) << "red";
						}
						else if (set[1][1] == 'g')
						{
							cout << left << setw(colorWidth) << setfill(separator) << "green";
						}
						else if (set[1][1] == 'p')
						{
							cout << left << setw(colorWidth) << setfill(separator) << "purple";
						}
						if (set[1][2] == 'f')
						{
							cout << left << setw(shadeWidth) << setfill(separator) << "filled";
						}
						else if (set[1][2] == 'o')
						{
							cout << left << setw(shadeWidth) << setfill(separator) << "open";
						}
						else if (set[1][2] == 's')
						{
							cout << left << setw(shadeWidth) << setfill(separator) << "striped";
						}
						if (set[1][3] == 'd')
						{
							cout << left << setw(shapeWidth) << setfill(separator) << "diamond";
						}
						else if (set[1][3] == 'o')
						{
							cout << left << setw(shapeWidth) << setfill(separator) << "oval";
						}
						else if (set[1][3] == 's')
						{
							cout << left << setw(shapeWidth) << setfill(separator) << "squiggle";
						}

						if (set[2][0] == '1')
						{
							cout << left << setw(numWidth) << setfill(separator) << "1";
						}
						else if (set[2][0] == '2')
						{
							cout << left << setw(numWidth) << setfill(separator) << "2";
						}
						else if (set[2][0] == '3')
						{
							cout << left << setw(numWidth) << setfill(separator) << "3";
						}
						if (set[2][1] == 'r')
						{
							cout << left << setw(colorWidth) << setfill(separator) << "red";
						}
						else if (set[2][1] == 'g')
						{
							cout << left << setw(colorWidth) << setfill(separator) << "green";
						}
						else if (set[2][1] == 'p')
						{
							cout << left << setw(colorWidth) << setfill(separator) << "purple";
						}
						if (set[2][2] == 'f')
						{
							cout << left << setw(shadeWidth) << setfill(separator) << "filled";
						}
						else if (set[2][2] == 'o')
						{
							cout << left << setw(shadeWidth) << setfill(separator) << "open";
						}
						else if (set[2][2] == 's')
						{
							cout << left << setw(shadeWidth) << setfill(separator) << "striped";
						}
						if (set[2][3] == 'd')
						{
							cout << left << setw(shapeWidth) << setfill(separator) << "diamond";
						}
						else if (set[2][3] == 'o')
						{
							cout << left << setw(shapeWidth) << setfill(separator) << "oval";
						}
						else if (set[2][3] == 's')
						{
							cout << left << setw(shapeWidth) << setfill(separator) << "squiggle";
						}
						cout << endl << endl;
					}
				tmp3 = tmp3->next;
			}
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}

	// checks number of solutions
	if (solCount > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}