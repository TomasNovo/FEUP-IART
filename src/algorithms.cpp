#include "algorithms.h"

#include "mapLoader.h"
#include "macros.h"

Node* breadth(vector<Node*> currRow, int level)
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
					nextNode = operations[j](currNode, robotIndex);
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


Node* breadth2(unordered_set<Node*, hashNode, hashNode> tree, vector<Node*> currRow, int level)
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
				nextNode = operations[j](currNode, robotIndex);
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


	return breadth2(tree, nextRow, level+1);
}

/*
Node* depth(Node* currNode, vector<Operator> operations, vector<string> operationNames, int level, int limit)
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
					Node* nextCall = depth(nextNode, level+1, limit);

					if (nextCall != NULL)
						return nextCall;
				}
			}
		}
	}


	return NULL;
}

*/




Node* greedy(unordered_set<Node*, hashNode, hashNode>& tree, Node* currNode, int level)
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
			nextNode = operations[i](currNode, robotIndex);
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

		Node* nextCall = greedy(tree, nextNode, level+1);

		if (nextCall != NULL)
			return nextCall;

		nextRow.pop();
	}


	return NULL;
}


multiset<Node*, sortF>::iterator linearSearchSet(multiset<Node*, sortF> input, Node* node)
{
	multiset<Node*, sortF>::iterator it;
	for (it = input.begin(); it != input.end() && (*it)->state != node->state; ++it)
	{}

	return it;
}


Node* aStar(Node* currNode, int level)
{
	multiset<Node*, sortF> openList;
	multiset<Node*, sortF> closedList;
	
	openList.insert(currNode);

	Node* nextNode;

	multiset<Node*, sortF>::iterator it;

	int iteCounter = 0;
	while (openList.size() > 0)
	{
		it = openList.begin();
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
				nextNode = operations[i](currNode, robotIndex);
				nextNode->cost++;
				nextNode->parent = currNode;
				nextNode->operationName = operationNames[i];
				nextNode->setH();
				
				if (DEBUG)
					cout << *nextNode << "\n";

				for (it = closedList.begin(); it != closedList.end() && (*it)->state != nextNode->state; ++it) // Search closedList for nextNode
				{}

				if (nextNode->state != currNode->state && it == closedList.end())
				{
					for (it = openList.begin(); it != openList.end() && (*it)->state != nextNode->state; ++it) // Search openList for nextNode
					{}
					
					if (it == openList.end())
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

Node* aStar2(Node* currNode, int level)
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
				nextNode = operations[i](currNode, robotIndex);
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