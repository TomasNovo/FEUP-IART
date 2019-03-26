#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <queue>
#include <functional>
#include <time.h> 
#include <algorithm>

#include "node.h"
#include "mapLoader.h"
#include "ui_utilities.h"

#define DEBUG 0

using namespace std;

typedef Node* (*Operator)(Node*, int, std::vector<std::vector<char> >);


void printSet(unordered_set<Node*, hashNode, hashNode> tree)
{
	for (auto it = tree.begin(); it != tree.end(); ++it)
	{
		cout << (**it) << "\n";
	}

	cout << "\n";
}


Node* breadth(vector<Node*> currRow, vector<vector<char>> map, vector<Operator> operations, string operationNames[], int level)
{
	if (currRow.size() == 0)
	{
		return NULL;
	}

	Node* currNode = new Node();
	Node* nextNode = new Node();

	vector<Node*> nextRow;

	while (1)
	{
		for (int i = 0; i < currRow.size(); i++)
		{
			currNode = currRow[i];
			// cout << *currNode << "\n";

			for (int robotIndex = 0; robotIndex < currNode->state.size(); robotIndex++)
			{
				for (int j = 0; j < operations.size(); j++)
				{
					nextNode = operations[j](currNode, robotIndex, map);
					nextNode->cost++;
					nextNode->parent = currNode;
					nextNode->operationName = operationNames[j];

					// cout << *nextNode << "\n";

					if (nextNode->finished())
					{
						return nextNode;
					}

					if (nextNode->parent == NULL || nextNode->state != nextNode->parent->state) // Checks if the state is the same after the operation
					{
						if (nextNode->parent->parent == NULL || nextNode->state != nextNode->parent->parent->state) // Checks if the state doesn't change from 2 levels above
						{
							nextRow.push_back(nextNode);
						}
					}
				}
			}
			
		}

		currRow = nextRow;
		nextRow.resize(0);
	}


	return NULL;
}


Node* breadth2(unordered_set<Node*, hashNode, hashNode> tree, vector<Node*> currRow, vector<vector<char>> map, vector<Operator> operations, string operationNames[], int level)
{
	if (currRow.size() == 0)
	{
		if (DEBUG)
			cout << "Tree size = " << tree.size() << "\n";

		return NULL;
	}

	Node* currNode;
	Node* nextNode;
	vector<int> operationHolder;

	vector<Node*> nextRow;

	for (int i = 0; i < currRow.size(); i++)
	{
		currNode = currRow[i];

		if (DEBUG)
			cout << *currNode << "\n";

		for (int robotIndex = 0; robotIndex < currNode->state.size(); robotIndex++)
		{
			for (int j = 0; j < operations.size(); j++)
			{
				nextNode = operations[j](currNode, robotIndex, map);
				nextNode->cost++;
				nextNode->parent = currNode;
				nextNode->operationName = operationNames[j];

				if (nextNode->finished())
				{
					if (DEBUG)
						cout << "Tree size = " << tree.size() << "\n";

					return nextNode;
				}

				if (tree.insert(nextNode).second)
				{
					if (DEBUG)
						cout << *nextNode << "\n";

					nextRow.push_back(nextNode);
				}
				else
				{
					delete nextNode;
				}
			}
		}

	}


	return breadth2(tree, nextRow, map, operations, operationNames, level+1);
}

/*
Node* depth(Node* currNode, vector<Operator> operations, string operationNames[], int level, int limit)
{
	if (currNode == NULL)
	{
		return NULL;
	}

	Node* nextNode = new Node();
	vector<int> operationHolder;

	vector<Node*> nextRow;

	// printSet(tree);
	for (int i = 0; i < operations.size(); i++)
	{
		operationHolder = operations[i](currNode->state);
		nextNode = new Node(operationHolder[0], operationHolder[1], currNode->cost+operationHolder[2]);
		nextNode->parent = currNode;
		nextNode->operationName = operationNames[i];

		if (nextNode->finished())
		{
			return nextNode;
		}

		if (nextNode->parent == NULL || nextNode->state != nextNode->parent->state) // Checks if the state is the same after the operation
		{
			if (nextNode->parent->parent == NULL || nextNode->state != nextNode->parent->parent->state) // Checks if the state doesn't change from 2 levels above
			{
				if (level+1 <= limit)
				{
					Node* nextCall = depth(nextNode, operations, operationNames, level+1, limit);

					if (nextCall != NULL)
						return nextCall;
				}
			}
		}
	}


	return NULL;
}

*/




Node* greedy(unordered_set<Node*, hashNode, hashNode>& tree, Node* currNode, vector<vector<char>> map, vector<Operator> operations, string operationNames[], int level)
{
	if (currNode == NULL/* || level == 10*/)
	{
		return new Node();
	}

	if (DEBUG)
	{
		cout << *currNode << "\n\n";
	}

	Node* nextNode;

	priority_queue<Node*, vector<Node*>, sortH> nextRow;

	for (int robotIndex = 0; robotIndex < currNode->state.size(); robotIndex++)
	{
		for (int i = 0; i < operations.size(); i++)
		{
			nextNode = operations[i](currNode, robotIndex, map);
			nextNode->cost++;
			nextNode->parent = currNode;
			nextNode->operationName = operationNames[i];

			if (nextNode->finished())
			{
				if (DEBUG)
				{
					cout << "Level: " << level << "\n";
				}

				return nextNode;
			}

			if (tree.insert(nextNode).second)
			{
				nextNode->setH();
				nextRow.push(nextNode);

				if (DEBUG)
				{
					cout << *nextNode << "\n\n";
				}
			}
		}
	}

	while (nextRow.size() > 0)
	{
		nextNode = nextRow.top();

		if (DEBUG)
		{
			cout << *nextNode << "\n\n";
		}

		Node* nextCall = greedy(tree, nextNode, map, operations, operationNames, level+1);

		if (nextCall != NULL)
			return nextCall;

		nextRow.pop();
	}


	return NULL;
}


multiset<Node*, sortF>::iterator linearSearchSet(multiset<Node*, sortF> input, Node* node)
{
	multiset<Node*, sortF>::iterator it;
	for (it = input.begin(); it != input.end(); ++it)
	{
		if ((*it)->state == node->state)
			return it;
	}

	return it;
}


Node* aStar(Node* currNode, vector<vector<char>> map, vector<Operator> operations, string operationNames[], int level)
{
	multiset<Node*, sortF> openList;
	multiset<Node*, sortF> closedList;
	
	openList.insert(currNode);

	Node* nextNode;

	while (openList.size() > 0)
	{
		multiset<Node*, sortF>::iterator it = openList.begin();
		currNode = *(it);

		if (currNode->finished())
		{
			return currNode;
		}

		openList.erase(it);

		closedList.insert(currNode);

		if (DEBUG)
			cout << *currNode << "\n";

		for (int robotIndex = 0; robotIndex < currNode->state.size(); robotIndex++)
		{
			for (int i = 0; i < operations.size(); i++)
			{
				nextNode = operations[i](currNode, robotIndex, map);
				nextNode->cost++;
				nextNode->parent = currNode;
				nextNode->operationName = operationNames[i];
				nextNode->setH();
				
				it = linearSearchSet(closedList, nextNode);

				if (nextNode->state != currNode->state && *it == *closedList.end())
				{
					it = linearSearchSet(openList, nextNode);
					
					if (*it == *openList.end())
					{
						openList.insert(nextNode);
					}
					else
					{
						if (nextNode->cost < (*it)->cost)
						{
							openList.erase(it);
							openList.insert(nextNode);
						}
					}
				}
				
			}
		}
	}

	return NULL;
}

Node* aStar2(Node* currNode, vector<vector<char>> map, vector<Operator> operations, string operationNames[], int level)
{
	multiset<Node*, sortF> openList;
	unordered_set<Node*, hashNode, hashNode> openSet;

	multiset<Node*, sortF> closedList;
	unordered_set<Node*, hashNode, hashNode> closedSet;

	openList.insert(currNode);
	openSet.insert(currNode);

	Node* nextNode;

	while (openList.size() > 0)
	{
		multiset<Node*, sortF>::iterator it = openList.begin();
		currNode = *(it);

		if (currNode->finished())
		{ 
			return currNode;
		}

		openList.erase(it);
		openSet.erase(currNode);

		closedList.insert(currNode);
		closedSet.insert(currNode);

		if (DEBUG)
			cout << *currNode << "\n";

		for (int robotIndex = 0; robotIndex < currNode->state.size(); robotIndex++)
		{
			for (int i = 0; i < operations.size(); i++)
			{
				nextNode = operations[i](currNode, robotIndex, map);
				nextNode->cost++;
				nextNode->parent = currNode;
				nextNode->operationName = operationNames[i];
				nextNode->setH();
				
				if (closedSet.find(nextNode) == closedSet.end())
				{
					auto it = openSet.find(nextNode);
					
					if (it == openSet.end())
					{
						openList.insert(nextNode);
						openSet.insert(nextNode);
					}
					else
					{
						if (nextNode->cost < (*it)->cost)
						{
							openList.erase(*it);
							openSet.erase(*it);

							openList.insert(nextNode);
							openSet.insert(nextNode);
						}
					}
				}
				
			}
		}
	}

	return NULL;
}


void printPath(Node* node)
{
	if (node == NULL)
		return;

	vector<string> path;
	vector<Node*> nodes;

	while (node->parent != NULL) // Until reaches root node
	{
		path.push_back(node->operationName);
		nodes.push_back(node);

		node = node->parent;
	}

	cout << "Path:\n";
	cout << printState(node->state);
	cout << "\n\n";

	for (int i = path.size()-1; i >= 0; i--)
	{
		cout << path[i] << "\n";
		
		if (DEBUG)
			cout << *nodes[i];
		else
			cout << printState(nodes[i]->state);
		
		cout << "\n\n";
	}

	cout << "Path size: " << path.size() << "\n";

}


void printMap(vector<vector<char>> map, Node* node)
{
	for (int i = 0; i < map.size(); ++i)
	{
		for (int j = 0; j < map[i].size(); ++j)
		{
			int k;
			if (node != NULL)
			{
				for (k = 0; k < node->state.size(); ++k)
				{
					if (i == node->state[k].coords[1] && j == node->state[k].coords[0]) // robot's position
					{
						cout << (char)(node->state[k].id + ('A' - 'a'));
						break;
					}

					else if (i == node->state[k].objective[1] && j == node->state[k].objective[0]) // robot's position
					{
						cout << (char)node->state[k].id;
						break;
					}
				}
			}
			
			if (node == NULL || k == node->state.size())
			{
				if (map[i][j] == '2' || map[i][j] == '0')
				cout << " ";

				else if (map[i][j] == '1')
					cout << 0;

				else
					cout << map[i][j];
			}

			cout << " ";
		}

		cout << "\n";
	}
}

void printPath2(Node* node, vector<vector<char>> map)
{
	if (node == NULL)
		return;

	vector<string> path;
	vector<Node*> nodes;

	while (node != NULL) // Until reaches root node
	{
		path.push_back(node->operationName);
		nodes.push_back(node);

		node = node->parent;
	}

	for (int i = path.size()-1; i >= 0; i--)
	{
		ui_utilities::ClearScreen();
		printMap(map, nodes[i]);
		cout << "\n\n";

		ui_utilities::milliSleep(2000); //sleeps for 1 second
	}
}


void printPath3(Node* node, vector<vector<char>> map)
{
	if (node == NULL)
		return;

	vector<string> path;
	vector<Node*> nodes;

	while (node != NULL) // Until reaches root node
	{
		path.push_back(node->operationName);
		nodes.push_back(node);

		node = node->parent;
	}

	int flashTime = 100, walkTime = 200, stopTime = 500;
	Node *currNode = new Node(*nodes.back()), *nextNode;
	vector<Robot> stateSave = currNode->state;

	for (int i = 0; i < 15; ++i) // start flashing animation
	{
		if (i % 2 == 0)
		{
			currNode->state.resize(0);
		}
		else
		{
			currNode->state = stateSave;
		}

		ui_utilities::ClearScreen();
		printMap(map, currNode);
		cout << "\n\n";
		ui_utilities::milliSleep(flashTime); //sleeps for 100 milliseconds
	}
	currNode->state = stateSave;

	ui_utilities::ClearScreen();
	printMap(map, currNode);
	cout << "\n\n";
	ui_utilities::milliSleep(stopTime*2); //sleeps for 1 second


	for (int i = path.size()-1; i >= 1; i--) // walking animation
	{
		currNode = new Node(*nodes[i]);
		nextNode = nodes[i-1];

		for (int j = 0; j < currNode->state.size(); ++j)
		{
			if (currNode->state[j].coords[1] != nextNode->state[j].coords[1])
			{
				int deltaY = nextNode->state[j].coords[1] - currNode->state[j].coords[1];

				for (int k = 0; k < abs(deltaY); ++k)
				{
					currNode->state[j].coords[1] += deltaY/abs(deltaY);
					ui_utilities::ClearScreen();
					printMap(map, currNode);
					cout << "\n\n";
					ui_utilities::milliSleep(walkTime); //sleeps for 200 milliseconds

				}
			}
			else if (currNode->state[j].coords[0] != nextNode->state[j].coords[0])
			{
				int deltaX = nextNode->state[j].coords[0] - currNode->state[j].coords[0];

				for (int k = 0; k < abs(deltaX); ++k)
				{
					currNode->state[j].coords[0] += deltaX/abs(deltaX);
					ui_utilities::ClearScreen();
					printMap(map, currNode);
					cout << "\n\n";
					ui_utilities::milliSleep(walkTime); //sleeps for 200 milliseconds

				}
			}	
		}

		if (i >= 2)
			ui_utilities::milliSleep(stopTime); //sleeps for 500 milliseconds
	}


	stateSave = currNode->state;
	for (int i = 0; i < 16; ++i) // end flashing animation
	{
		if (i % 2 == 0)
		{
			currNode->state.resize(0);
		}
		else
		{
			currNode->state = stateSave;
		}

		ui_utilities::ClearScreen();
		printMap(map, currNode);
		cout << "\n\n";
		ui_utilities::milliSleep(flashTime); //sleeps for 500 milliseconds
	}

	cout << "Path size: " << path.size()-1 << "\n\n";
}

bool validMove(Node* node, int robotIndex, vector<vector<char>> map, int x, int y)
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

int menu()
{
	ui_utilities::ClearScreen();

	int input;

	cout << endl << "------------------------------------" << endl;
	cout << "|                                  |" << endl;
	cout << "|  L A B Y R I N T H   R O B O T S |" << endl;
	cout << "|                                  |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 1 - Play                         |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 2 - Watch an agent play          |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 3 - Info                         |" << endl;
	cout << "------------------------------------" << endl;
	cout << endl << endl << "Input: ";

	cin >> input;
	while (cin.fail() || input > 3 || input < 1)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nChoose a valid number please ! \n\n";
			cout << "Input: ";
			cin >> input;
		}


	return input;
}


void agent()
{
	Operator up = [](Node* node, int robotIndex, vector<vector<char>> map) { Node* newNode = new Node(*node); int i; for (i = newNode->state[robotIndex].coords[1]; i >= 0; i--) { if (!validMove(newNode, robotIndex, map, newNode->state[robotIndex].coords[0], i)) {break;}} newNode->state[robotIndex].coords[1] = i+1; return newNode;};
	Operator right = [](Node* node, int robotIndex, vector<vector<char>> map) { Node* newNode = new Node(*node); int i; for (i = newNode->state[robotIndex].coords[0]; i < map[newNode->state[robotIndex].coords[1]].size(); i++) { if (!validMove(newNode, robotIndex, map, i, newNode->state[robotIndex].coords[1])) {break;}} newNode->state[robotIndex].coords[0] = i-1; return newNode;};
	Operator down = [](Node* node, int robotIndex, vector<vector<char>> map) { Node* newNode = new Node(*node); int i; for (i = newNode->state[robotIndex].coords[1]; i < map.size(); i++) { if (!validMove(newNode, robotIndex, map, newNode->state[robotIndex].coords[0], i)) {break;}} newNode->state[robotIndex].coords[1] = i-1; return newNode;};
	Operator left = [](Node* node, int robotIndex, vector<vector<char>> map) { Node* newNode = new Node(*node); int i; for (i = newNode->state[robotIndex].coords[0]; i >= 0; i--) { if (!validMove(newNode, robotIndex, map, i, newNode->state[robotIndex].coords[1])) {break;}} newNode->state[robotIndex].coords[0] = i+1; return newNode;};

	vector<Operator> operations = {up, right, down, left};
	string operationNames[] = {"up", "right", "down", "left"};

	vector<Robot> startState;

	vector<vector<char>> map = loadMap("map.txt", startState);
	
	Node* rootNode = new Node();
	rootNode->state = startState;
	rootNode->setH();

	vector<Node*> rootRow;
	rootRow.push_back(rootNode);

	unordered_set<Node*, hashNode, hashNode> tree;
	tree.insert(rootNode);

	Node* result = NULL;
	
	clock_t time = clock();

	for (int i = 0; i < 1; i++)
	{
		// result = breadth(rootRow, map, operations, operationNames, 0);
		// result = breadth2(tree, rootRow, map, operations, operationNames, 0);
		// result = depth(rootNode, operations, operationNames, 0, 12);
		// result = greedy(tree, rootNode, map, operations, operationNames, 0);
		// result = aStar(rootNode, map, operations, operationNames, 0);
		result = aStar2(rootNode, map, operations, operationNames, 0);
	}

	double deltaTime = (double)(clock()-time)/CLOCKS_PER_SEC;

	cout << "\n";
	
	if (DEBUG)
		printPath(result);
	else
		printPath3(result, map);

	printf("\nFinished in %f seconds.\n", deltaTime);
}




int main()
{
	int input = menu();

	if (input == 1)
	{
		// play
	}
	else if (input == 2)
		agent();

	return 0;
}