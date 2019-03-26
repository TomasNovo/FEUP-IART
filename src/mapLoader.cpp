#include "mapLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>

vector<vector<char>> map;

vector<Operator> operations;
vector<string> operationNames;


bool validMove(Node* node, int robotIndex, int x, int y)
{
	if (x < 0 || x >= map[0].size() || y < 0 || y >= map.size() || map[y][x] == '1')
		return false;

	for (int i = 0; i < node->state.size(); ++i)
	{
		if (i != robotIndex && node->state[i].coords[0] == x && node->state[i].coords[1] == y)
			return false;
	}

	return true;
}

Node* initiateMap(string filename)
{
	initiateOperators();
	
	vector<Robot> startState;

	loadMap(filename, startState);
	
	Node* rootNode = new Node();
	rootNode->state = startState;
	rootNode->setH();

	return rootNode;
}

void loadMap(string filename, vector<Robot>& robots)
{
	ifstream ifs(filename);
	string line, cell;
	char cellValue;

	robots.resize(0);

	while (getline(ifs, line))
	{
		if (!((line[0] >= 'A' && line[0] <= 'Z') || (line[0] >= 'a' && line[0] <= 'z') || (line[0] >= '0' && line[0] <= '9')))
			continue;
	
		if (line.back() != ',')
			line.push_back(',');

		stringstream ss(line);
		vector<char> row = vector<char>();
		for (int i = 0; getline(ss, cell, ','); ++i)
		{
			cellValue = cell[0];

			if (!(cellValue >= '0' && cellValue <= '9')) // Not numeric 
			{
				char id;
				Robot robot;

				if (cellValue >= 'A' && cellValue <= 'Z') // Converts char to lower for id
					id = cellValue + ('a' - 'A');
				else
					id = cellValue;

				int index = -1;
				for (index = 0; index < robots.size() && robots[index].id != id; ++index) // Search robots for the same robot (equal id)
				{}

				if (index == robots.size())
				{
					robot = Robot();
					robot.id = id;
					robots.push_back(robot);
				}
				else
				{
					robot = robots[index];
				}

				if (cellValue >= 'a' && cellValue <= 'z') // Objective
				{
					robot.objective[0] = row.size();
					robot.objective[1] = map.size();
				}
				else if (cellValue >= 'A' && cellValue <= 'Z') // Robot
				{
					robot.coords[0] = row.size();
					robot.coords[1] = map.size();
				}

				robots[index] = robot;

				cellValue = '0';
			}

			row.push_back(cellValue);
		}

		map.push_back(row);
	}
}


void initiateOperators()
{
	Operator up = [](Node* node, int robotIndex) { Node* newNode = new Node(*node); int i; for (i = newNode->state[robotIndex].coords[1]; i >= 0; i--) { if (!validMove(newNode, robotIndex, newNode->state[robotIndex].coords[0], i)) {break;}} newNode->state[robotIndex].coords[1] = i+1; return newNode;};
	Operator right = [](Node* node, int robotIndex) { Node* newNode = new Node(*node); int i; for (i = newNode->state[robotIndex].coords[0]; i < map[newNode->state[robotIndex].coords[1]].size(); i++) { if (!validMove(newNode, robotIndex, i, newNode->state[robotIndex].coords[1])) {break;}} newNode->state[robotIndex].coords[0] = i-1; return newNode;};
	Operator down = [](Node* node, int robotIndex) { Node* newNode = new Node(*node); int i; for (i = newNode->state[robotIndex].coords[1]; i < map.size(); i++) { if (!validMove(newNode, robotIndex, newNode->state[robotIndex].coords[0], i)) {break;}} newNode->state[robotIndex].coords[1] = i-1; return newNode;};
	Operator left = [](Node* node, int robotIndex) { Node* newNode = new Node(*node); int i; for (i = newNode->state[robotIndex].coords[0]; i >= 0; i--) { if (!validMove(newNode, robotIndex, i, newNode->state[robotIndex].coords[1])) {break;}} newNode->state[robotIndex].coords[0] = i+1; return newNode;};

	operations = {up, right, down, left};
	operationNames = {"up", "right", "down", "left"};
}