/*
Student Name: Rachel Jordan
Student NetID: rej168
Compiler Used: Visual Studio
Program Description: A program that can create and solve puzzles based on the SET puzzle
*/

#pragma once
#include <string>

using std::string;

class Card
{
public:
	// all the data
	int number;
	string color;
	string shading;
	string shape;
	Card* next;

	// universal constructor based on Node universal constructor from lecture notes
	Card() : number(0), color(""), shading(""), shape(""), next(nullptr) {}
	Card(Card* next) : number(0), color(""), shading(""), shape(""), next(next) {}
	Card(int number, string color, string shading, string shape) : number(number), color(color), shading(shading), shape(shape), next(next) {}
	Card(int number, string color, string shading, string shape, Card* next) : number(number), color(color), shading(shading), shape(shape), next(next) {}

};