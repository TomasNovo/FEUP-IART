#include "mapLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "macros.h"

std::vector<std::vector<char>> map;

std::vector<Operator> operations;
std::vector<std::string> operationNames;


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

Node* initiateMap()
{
	initiateOperators();
		
	Node* rootNode = new Node();
	rootNode->setH(0);

	return rootNode;
}

void createMap()
{
	std::vector<int> row(MAPWIDTH, 0);
	std::vector<std::vector<int>> map(MAPHEIGHT, row);
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