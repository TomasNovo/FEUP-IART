#include "mapLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "macros.h"

std::vector<std::vector<char>> map;

std::vector<Operator> operations;
std::vector<std::string> operationNames;


bool validMove(Node* node, int characterIndex, int deltaX, int deltaY)
{
	int x = node->state[characterIndex].coords[0];
	int y = node->state[characterIndex].coords[1];
	int newX = x + deltaX;
	int newY = y + deltaY;

	if (newX < 0 || newX >= MAPWIDTH || newY < 0 || newY >= MAPHEIGHT)
		return false;

	for (int i = 0; i < node->state.size(); ++i)
	{
		if (i != characterIndex && node->state[i].coords[0] == newX && node->state[i].coords[1] == newY)
			return false;

		for (auto wall : node->state[i].walls)
		{
			std::string wallType = wall.substr(0, 6);
			int wallI = stoi(wall.substr(6, 1));
			int wallJ = stoi(wall.substr(7, 1));

			if (deltaX != 0 && wallType == "barVer" && (wallI == y  || wallI == y-1))
			{
				if (deltaX == -1)
				{
					if (wallJ == newX)
						return false;
				}
				else
				{
					if (wallJ == newX - 1)
						return false;
				}
			}

			if (deltaY != 0 && wallType == "barHor" && (wallJ == x || wallJ == x - 1))
			{
				if (deltaY == -1)
				{
					if (wallI == newY)
						return false;
				}
				else
				{
					if (wallI == newY - 1)
						return false;
				}
			}

		}
	}

	return true;
}

bool validBar(Node* node, int characterIndex, std::string type, int i, int j)
{
	if (i < 0 || i >= MAPWIDTH-1 || j < 0 || j >= MAPHEIGHT-1)
		return false;

	for (int k = 0; k < node->state.size(); ++k)
	{
		for (auto wall : node->state[k].walls)
		{
			std::string wallType = wall.substr(0, 6);
			int wallI = stoi(wall.substr(6, 1));
			int wallJ = stoi(wall.substr(7, 1));

			if (type == "barVer")
			{
				if (wallType == "barVer" && wallI == i && wallJ == j)
					return false;

				if (wallType == "barVer" && wallI == i + 1 && wallJ == j)
					return false;

				if (wallType == "barHor" && wallI == i && wallJ == j)
					return false;
			}
			else if (type == "barHor")
			{
				if (wallType == "barHor" && wallI == i && wallJ == j)
					return false;

				if (wallType == "barHor" && wallI == i && wallJ == j + 1)
					return false;

				if (wallType == "barVer" && wallI == i && wallJ == j)
					return false;
			}

		}
	}

	node = new Node(*node);
	node->state[characterIndex].addWall(type + std::to_string(i) + std::to_string(j));

	for (int k = 0; k < node->state.size(); ++k)
	{
		if (node->getDistance(k) == -1)
		{
			delete node;
			return false;
		}
	}

	delete node;
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
	Operator up = [](Node* node, int characterIndex) {Node* newNode = new Node(*node); if (validMove(newNode, characterIndex, 0, -1)) { newNode->state[characterIndex].coords[1]--; } return newNode; };
	Operator right = [](Node* node, int characterIndex) {Node* newNode = new Node(*node); if (validMove(newNode, characterIndex, 1, 0)) { newNode->state[characterIndex].coords[0]++; } return newNode;};
	Operator down = [](Node* node, int characterIndex) {Node* newNode = new Node(*node); if (validMove(newNode, characterIndex, 0, 1)) { newNode->state[characterIndex].coords[1]++; } return newNode;};
	Operator left = [](Node* node, int characterIndex) {Node* newNode = new Node(*node); if (validMove(newNode, characterIndex, -1, 0)) { newNode->state[characterIndex].coords[0]--; } return newNode;};

	operations.push_back(up);
	operations.push_back(right);
	operations.push_back(down);
	operations.push_back(left);

	operationNames.push_back("up");
	operationNames.push_back("right");
	operationNames.push_back("down");
	operationNames.push_back("left");

	for (size_t i = 0; i < MAPHEIGHT - 1; i++)
	{
		for (size_t j = 0; j < MAPWIDTH - 1; j++)
		{
			Operator opVer = [&](Node* node, int characterIndex)
			{
				Node* newNode = new Node(*node);
				
				if (validBar(newNode, characterIndex,  "barVer", i , j))
					newNode->state[characterIndex].addWall("barVer" + std::to_string(i) + std::to_string(j));

				return newNode;
			};

			Operator opHor = [&](Node* node, int characterIndex)
			{
				Node* newNode = new Node(*node);

				if (validBar(newNode, characterIndex, "barHor", i, j))
					newNode->state[characterIndex].addWall("barHor" + std::to_string(i) + std::to_string(j));

				return newNode;
			};

			operations.push_back(opVer);
			operationNames.push_back("barVer" + std::to_string(i) + std::to_string(j));

			operations.push_back(opHor);
			operationNames.push_back("barHor" + std::to_string(i) + std::to_string(j));
		}
	}
}

Node* doOperation(Node* currNode, int i, int characterIndex)
{
	Node* newNode = operations[i](currNode, characterIndex);

	newNode->cost++;
	newNode->setH(0);
	newNode->parent = currNode;
	newNode->operationName = operationNames[i];

	return newNode;
}


bool removeOperation(std::string operationName)
{
	for (size_t i = 0; i < operationNames.size(); i++)
	{
		if (operationNames[i] == operationName)
		{
			operations.erase(operations.begin() + i);
			operationNames.erase(operationNames.begin() + i);
			return true;
		}
	}

	return false;
}