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
	if (i < 0 || i >= MAPWIDTH-1 || j < 0 || j >= MAPHEIGHT-1 || node->state[characterIndex].walls.size() == MAXWALLCOUNT)
		return false;

	for (int k = 0; k < node->state.size(); ++k)
	{
		for (auto wall : node->state[k].walls)
		{
			std::string wallType = wall.substr(0, 6);
			int wallI = wall[6] - '0';
			int wallJ = wall[7] - '0';

			if (wallsCollide(type, i, j, wallType, wallI, wallJ))
				return false;
		}
	}

	Node* testNode = new Node(*node);
	testNode->state[characterIndex].addWall(type + std::to_string(i) + std::to_string(j));
	bool valid = true;
	
	for (size_t i = 0; i < testNode->state.size(); i++)
	{
		int characterH = testNode->getDistance(i);

		if (characterH == -1)
		{
			valid = false;
			break;
		}
	}

	delete testNode;
	return valid;
}

bool validBarEfficient(Node* node, int characterIndex, std::string type, int i, int j, int maxCharacter)
{
	if (i < 0 || i >= MAPWIDTH - 1 || j < 0 || j >= MAPHEIGHT - 1 || node->state[characterIndex].walls.size() == MAXWALLCOUNT)
		return false;

	for (int k = 0; k < node->state.size(); ++k)
	{
		for (auto wall : node->state[k].walls)
		{
			std::string wallType = wall.substr(0, 6);
			int wallI = wall[6] - '0';
			int wallJ = wall[7] - '0';

			if (wallsCollide(type, i, j, wallType, wallI, wallJ))
				return false;
		}
	}

	Node* testNode = new Node(*node);
	testNode->state[characterIndex].addWall(type + std::to_string(i) + std::to_string(j));
	bool valid = true;

	testNode->h = 0;

	for (size_t i = 0; i < testNode->state.size(); i++) // Runs testNode->setH(maxCharacter)
	{
		int characterH = testNode->getDistance(i);

		if (characterH == -1)
		{
			valid = false;
			break;
		}

		if (i == maxCharacter)
			testNode->h -= characterH;
		else
			testNode->h += characterH / (double)(testNode->state.size() - 1);
	}

	testNode->f = testNode->cost + testNode->h;

	if (valid)
	{
		node->h = testNode->h;
		node->f = testNode->f;
	}
	
	delete testNode;

	return valid;
}

bool wallsCollide(std::string type1, int i1, int j1, std::string type2, int i2, int j2)
{
	if (type1 == "barVer")
	{
		if (type2 == "barVer" && i2 == i1 && j2 == j1)
			return true;

		if (type2 == "barVer" && i2 == i1 + 1 && j2 == j1)
			return true;

		if (type2 == "barVer" && i2 + 1 == i1 && j2 == j1)
			return true;

		if (type2 == "barHor" && i2 == i1 && j2 == j1)
			return true;
	}
	else if (type1 == "barHor")
	{
		if (type2 == "barHor" && i2 == i1 && j2 == j1)
			return true;

		if (type2 == "barHor" && i2 == i1 && j2 == j1 + 1)
			return true;

		if (type2 == "barHor" && i2 == i1 && j2 + 1 == j1)
			return true;

		if (type2 == "barVer" && i2 == i1 && j2 == j1)
			return true;
	}

	return false;
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
	Operator up = [](Node* node, int characterIndex) {Node* newNode = node; if (validMove(newNode, characterIndex, 0, -1)) { newNode = new Node(*node); newNode->state[characterIndex].coords[1]--; } return newNode; };
	Operator right = [](Node* node, int characterIndex) {Node* newNode = node; if (validMove(newNode, characterIndex, 1, 0)) { newNode = new Node(*node); newNode->state[characterIndex].coords[0]++; } return newNode;};
	Operator down = [](Node* node, int characterIndex) {Node* newNode = node; if (validMove(newNode, characterIndex, 0, 1)) { newNode = new Node(*node); newNode->state[characterIndex].coords[1]++; } return newNode;};
	Operator left = [](Node* node, int characterIndex) {Node* newNode = node; if (validMove(newNode, characterIndex, -1, 0)) { newNode = new Node(*node); newNode->state[characterIndex].coords[0]--; } return newNode;};

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
			Operator opVer = [i, j](Node* node, int characterIndex)
			{
				Node* newNode = node;
				
				if (validBar(newNode, characterIndex, "barVer", i, j))
				{
					newNode = new Node(*node);
					newNode->state[characterIndex].addWall("barVer" + std::to_string(i) + std::to_string(j));
				}

				return newNode;
			};

			Operator opHor = [i, j](Node* node, int characterIndex)
			{
				Node* newNode = node;

				if (validBar(newNode, characterIndex, "barHor", i, j))
				{
					newNode = new Node(*node);
					newNode->state[characterIndex].addWall("barHor" + std::to_string(i) + std::to_string(j));
				}

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

	if (newNode != currNode)
	{
		newNode->cost++;
		newNode->setH(0);

		newNode->parent = currNode;
		newNode->operationName = operationNames[i];
	}

	return newNode;
}

Node* doOperationEfficient(Node* currNode, int i, int characterIndex, int maxCharacter)
{
	Node* newNode;

	if (i < 4)
	{
		newNode = operations[i](currNode, characterIndex);

		if (newNode != currNode)
		{
			newNode->setH(maxCharacter);
			newNode->parent = currNode;
			newNode->cost++;
			newNode->operationName = operationNames[i];
		}
	}
	else
	{
		newNode = new Node(*currNode);
	
		std::string wall = operationNames[i];
		std::string wallType = wall.substr(0, 6);
		int wallI = wall[6] - '0';
		int wallJ = wall[7] - '0';

		if (validBarEfficient(newNode, characterIndex, wallType, wallI, wallJ, maxCharacter))
		{
			newNode->state[characterIndex].addWall(wall);
			newNode->parent = currNode;
			newNode->cost++;
			newNode->operationName = operationNames[i];

		}
		else
		{
			delete newNode;
			newNode = currNode;
		}
	}

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