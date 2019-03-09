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


void printSet(unordered_set<Node*, hashNode, hashNode> tree)
{
	for (auto it = tree.begin(); it != tree.end(); ++it)
	{
		cout << (**it) << "\n";
	}

	cout << "\n";
}


Node* breadth(vector<Node*> currRow, vector<int> objective, vector<vector<int>> map, vector<function<Node*(Node*, vector<vector<int>>)>> operations, string operationNames[], int level)
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

			for (int j = 0; j < operations.size(); j++)
			{
				nextNode = operations[j](currNode, map);
				nextNode->cost++;
				nextNode->parent = currNode;
				nextNode->operationName = operationNames[j];

				// cout << *nextNode << "\n";

				if (nextNode->state == objective)
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

		currRow = nextRow;
		nextRow.resize(0);
	}


	return NULL;
}


Node* breadth2(unordered_set<Node*, hashNode, hashNode> tree, vector<Node*> currRow, vector<int> objective, vector<vector<int>> map, vector<function<Node*(Node*, vector<vector<int>>)>> operations, string operationNames[], int level)
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

		for (int j = 0; j < operations.size(); j++)
		{
			nextNode = operations[j](currNode, map);
			nextNode->cost++;
			nextNode->parent = currNode;
			nextNode->operationName = operationNames[j];

			if (nextNode->state == objective)
			{
				if (DEBUG)
					cout << "Tree size = " << tree.size() << "\n";

				return nextNode;
			}

			if (tree.insert(nextNode).second)
			{
				nextRow.push_back(nextNode);
			}
			else
			{
				delete nextNode;
			}
		}
	}


	return breadth2(tree, nextRow, objective, map, operations, operationNames, level+1);
}

/*
Node* depth(Node* currNode, vector<int> objective, vector<function<vector<int>(vector<int>)>> operations, string operationNames[], int level, int limit)
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

		if (nextNode->state == objective)
		{
			return nextNode;
		}

		if (nextNode->parent == NULL || nextNode->state != nextNode->parent->state) // Checks if the state is the same after the operation
		{
			if (nextNode->parent->parent == NULL || nextNode->state != nextNode->parent->parent->state) // Checks if the state doesn't change from 2 levels above
			{
				if (level+1 <= limit)
				{
					Node* nextCall = depth(nextNode, objective, operations, operationNames, level+1, limit);

					if (nextCall != NULL)
						return nextCall;
				}
			}
		}
	}


	return NULL;
}

*/




Node* greedy(unordered_set<Node*, hashNode, hashNode>& tree, Node* currNode, vector<int> objective, vector<vector<int>> map, vector<function<Node*(Node*, vector<vector<int>>)>> operations, string operationNames[], int level)
{
	if (currNode == NULL/* || level == 10*/)
	{
		return new Node();
	}

	if (DEBUG)
	{
		cout << "h = " << currNode->h << "\n";
		cout << *currNode << "\n\n";
	}

	Node* nextNode;

	priority_queue<Node*, vector<Node*>, sortH> nextRow;

	for (int i = 0; i < operations.size(); i++)
	{
		nextNode = operations[i](currNode, map);
		nextNode->cost++;
		nextNode->parent = currNode;
		nextNode->operationName = operationNames[i];

		if (nextNode->state == objective)
		{ 
			return nextNode;
		}

		if (tree.insert(nextNode).second)
		{
			nextNode->setH(objective);
			nextRow.push(nextNode);
		}
	}

	while (nextRow.size() > 0)
	{
		nextNode = nextRow.top();

		// if (DEBUG)
		// {
		// 	cout << "h = " << nextNode->h << "\n";
		// 	cout << *nextNode << "\n\n";
		// }

		Node* nextCall = greedy(tree, nextNode, objective, map, operations, operationNames, level+1);

		if (nextCall != NULL)
			return nextCall;

		nextRow.pop();
	}


	return NULL;
}


multiset<Node*, sortH>::iterator linearSearchSet(multiset<Node*, sortH> input, Node* node)
{
	multiset<Node*, sortH>::iterator it;
	for (it = input.begin(); it != input.end(); ++it)
	{
		if ((*it)->state == node->state)
			return it;
	}

	return it;
}


Node* aStar(Node* currNode, vector<int> objective, vector<vector<int>> map, vector<function<Node*(Node*, vector<vector<int>>)>> operations, string operationNames[], int level)
{
	multiset<Node*, sortH> openList;
	multiset<Node*, sortH> closedList;
	
	openList.insert(currNode);

	Node* nextNode;

	while (openList.size() > 0)
	{
		multiset<Node*, sortH>::iterator it = openList.begin();
		currNode = *(it);

		if (currNode->state == objective)
		{ 
			return currNode;
		}

		openList.erase(it);

		closedList.insert(currNode);

		if (DEBUG)
			cout << *currNode << "\n";

		for (int i = 0; i < operations.size(); i++)
		{
			nextNode = operations[i](currNode, map);
			nextNode->cost++;
			nextNode->parent = currNode;
			nextNode->operationName = operationNames[i];
			nextNode->setH(objective);
			
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

	return NULL;
}

Node* aStar2(Node* currNode, vector<int> objective, vector<vector<int>> map, vector<function<Node*(Node*, vector<vector<int>>)>> operations, string operationNames[], int level)
{
	multiset<Node*, sortH> openList;
	unordered_set<Node*, hashNode, hashNode> openSet;

	multiset<Node*, sortH> closedList;
	unordered_set<Node*, hashNode, hashNode> closedSet;

	openList.insert(currNode);
	openSet.insert(currNode);

	Node* nextNode;

	while (openList.size() > 0)
	{
		multiset<Node*, sortH>::iterator it = openList.begin();
		currNode = *(it);

		if (currNode->state == objective)
		{ 
			return currNode;
		}

		openList.erase(it);
		openSet.erase(currNode);

		closedList.insert(currNode);
		closedSet.insert(currNode);

		if (DEBUG)
			cout << *currNode << "\n";

		for (int i = 0; i < operations.size(); i++)
		{
			nextNode = operations[i](currNode, map);
			nextNode->cost++;
			nextNode->parent = currNode;
			nextNode->operationName = operationNames[i];
			nextNode->setH(objective);
			
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


void printMap(vector<vector<int>> map, Node* node)
{
	for (int i = 0; i < map.size(); ++i)
	{
		for (int j = 0; j < map[i].size(); ++j)
		{
			if (node != NULL && i == node->state[1] && j == node->state[0]) // robot's position
				cout << 2;

			else if (map[i][j] == 2 || map[i][j] == 0)
				cout << " ";

			else if (map[i][j] == 1)
				cout << 0;

			else
				cout << map[i][j];

			cout << " ";
		}

		cout << "\n";
	}
}

void printPath2(Node* node, vector<vector<int>> map)
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


void printPath3(Node* node, vector<vector<int>> map)
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
	vector<int> stateSave = currNode->state;

	for (int i = 0; i < 15; ++i) // start flashing animation
	{
		if (i % 2 == 0)
		{
			currNode->state[0] = -1;
			currNode->state[1] = -1;
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

		if (currNode->state[0] == nextNode->state[0])
		{
			int deltaY = nextNode->state[1] - currNode->state[1];

			for (int j = 0; j < abs(deltaY); ++j)
			{
				currNode->state[1] += deltaY/abs(deltaY);
				ui_utilities::ClearScreen();
				printMap(map, currNode);
				cout << "\n\n";
				ui_utilities::milliSleep(walkTime); //sleeps for 200 milliseconds

			}
		}
		else
		{
			int deltaX = nextNode->state[0] - currNode->state[0];

			for (int j = 0; j < abs(deltaX); ++j)
			{
				currNode->state[0] += deltaX/abs(deltaX);
				ui_utilities::ClearScreen();
				printMap(map, currNode);
				cout << "\n\n";
				ui_utilities::milliSleep(walkTime); //sleeps for 200 milliseconds

			}
		}

		if (i >= 2)
			ui_utilities::milliSleep(stopTime); //sleeps for 500 milliseconds
	}


	stateSave = currNode->state;
	for (int i = 0; i < 15; ++i) // end flashing animation
	{
		if (i % 2 == 0)
		{
			currNode->state[0] = -1;
			currNode->state[1] = -1;
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
}


int main()
{
	function<Node*(Node*, vector<vector<int>>)> up = [](Node* node, vector<vector<int>> map) { Node* newNode = new Node(*node); int i; for (i = newNode->state[1]; i >= 0; i--) { if (map[i][newNode->state[0]] == 1) {break;}} newNode->state[1] = i+1; return newNode;};
	function<Node*(Node*, vector<vector<int>>)> right = [](Node* node, vector<vector<int>> map) { Node* newNode = new Node(*node); int i; for (i = newNode->state[0]; i < map[newNode->state[1]].size(); i++) { if (map[newNode->state[1]][i] == 1) {break;}} newNode->state[0] = i-1; return newNode;};
	function<Node*(Node*, vector<vector<int>>)> down = [](Node* node, vector<vector<int>> map) { Node* newNode = new Node(*node); int i; for (i = newNode->state[1]; i < map.size(); i++) { if (map[i][newNode->state[0]] == 1) {break;}} newNode->state[1] = i-1; return newNode;};
	function<Node*(Node*, vector<vector<int>>)> left = [](Node* node, vector<vector<int>> map) { Node* newNode = new Node(*node); int i; for (i = newNode->state[0]; i >= 0; i--) { if (map[newNode->state[1]][i] == 1) {break;}} newNode->state[0] = i+1; return newNode;};

	vector<function<Node*(Node*, vector<vector<int>>)>> operations = {up, right, down, left};
	string operationNames[] = {"up", "right", "down", "left"};

	vector<int> start;
	vector<int> objective;

	vector<vector<int>> map = loadMap("map2.txt", start, objective);
	
	Node* rootNode = new Node();
	rootNode->state = start;
	rootNode->setH(objective);

	vector<Node*> rootRow;
	rootRow.push_back(rootNode);

	priority_queue<Node*, vector<Node*>, sortH> rootRow2;
	rootRow2.push(rootNode);

	unordered_set<Node*, hashNode, hashNode> tree;
	tree.insert(rootNode);

	Node* result = NULL;

	// printMap(map, rootNode);
	
	clock_t time = clock();

	for (int i = 0; i < 1; i++)
	{
		// result = breadth(rootRow, objective, map, operations, operationNames, 0);
		// result = breadth2(tree, rootRow, objective, map, operations, operationNames, 0);
		// result = depth(rootNode, objective, operations, operationNames, 0, 12);
		// result = greedy(rootNode, tree, rootNode, objective, operations, operationNames, 0);
		result = aStar(rootNode, objective, map, operations, operationNames, 0);
		// result = aStar2(rootNode, objective, map, operations, operationNames, 0);
	}

	double deltaTime = (double)(clock()-time)/CLOCKS_PER_SEC;

	cout << "\n";
	
	if (DEBUG)
		printPath(result);
	else
		printPath3(result, map);

	printf("\nFinished in %f seconds.\n", deltaTime);

	return 0;
}