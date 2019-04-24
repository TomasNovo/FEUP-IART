#include "mapLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::vector<char>> map; // TODO remove this variable

std::vector<Operator> operations;
std::vector<std::string> operationNames;

#define MAPHEIGHT 9
#define MAPWIDTH 9


bool validMove(Node* node, int characterIndex, int x, int y)
{
	x += node->state[characterIndex].coords[0], y += node->state[characterIndex].coords[1];

	if (x < 0 || x >= MAPWIDTH || y < 0 || y >= MAPHEIGHT)
		return false;

	for (int i = 0; i < node->state.size(); ++i)
	{
		if (i != characterIndex && node->state[i].coords[0] == x && node->state[i].coords[1] == y)
			return false;
	}

	return true;
}

Node* initiateMap(std::string filename)
{
	initiateOperators();
	
	std::vector<Character> startState;
	
	Node* rootNode = new Node();
	rootNode->state = startState;
	rootNode->setH(0);

	return rootNode;
}

std::vector<std::vector<int>> createMap()
{
	
}


void initiateOperators()
{
	Operator up = [](Node* node, int characterIndex) {Node* newNode = new Node(*node); if (validMove(newNode, characterIndex, 0, -1)) { newNode->state[characterIndex].coords[1]--; } return newNode;};
	Operator right = [](Node* node, int characterIndex) {Node* newNode = new Node(*node); if (validMove(newNode, characterIndex, 1, 0)) { newNode->state[characterIndex].coords[0]++; } return newNode;};
	Operator down = [](Node* node, int characterIndex) {Node* newNode = new Node(*node); if (validMove(newNode, characterIndex, 0, 1)) { newNode->state[characterIndex].coords[1]++; } return newNode;};
	Operator left = [](Node* node, int characterIndex) {Node* newNode = new Node(*node); if (validMove(newNode, characterIndex, -1, 0)) { newNode->state[characterIndex].coords[0]--; } return newNode;};

	operations = {up, right, down, left};
	operationNames = {"up", "right", "down", "left"};
}