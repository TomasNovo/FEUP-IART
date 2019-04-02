#include "algorithms.h"

#include "mapLoader.h"
#include "macros.h"

Node* breadth(Node* currNode)
{
	if (currNode == NULL)
	{
		return NULL;
	}

	std::vector<Node*> currRow = {currNode};
	std::vector<Node*> nextRow;

	Node* nextNode;

	while (1)
	{
		for (int i = 0; i < currRow.size(); i++)
		{
			currNode = currRow[i];

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


Node* uniformCost(Node* currNode)
{
	if (currNode == NULL)
	{
		return NULL;
	}

	std::unordered_set<Node*, hashNode, hashNode> tree;

	std::vector<Node*> currRow = {currNode};
	std::vector<Node*> nextRow;

	Node* nextNode;

	while (1)
	{
		for (int i = 0; i < currRow.size(); i++)
		{
			currNode = currRow[i];

			if (DEBUG)
				std::cout << *currNode << "\n";

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
							std::cout << "Tree size = " << tree.size() << "\n";

						return nextNode;
					}

					if (tree.insert(nextNode).second)
					{
						if (DEBUG)
							std::cout << *nextNode << "\n";

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


Node* depth(Node* currNode, int level, const int& limit)
{
	if (currNode == NULL || level >= limit)
	{
		return NULL;
	}

	Node* nextNode = new Node();

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
					std::cout << "Level: " << level << "\n";

				return nextNode;
			}

			if (nextNode->parent == NULL || nextNode->state != nextNode->parent->state) // Checks if the state is the same after the operation
			{
				if (nextNode->parent->parent == NULL || nextNode->state != nextNode->parent->parent->state) // Checks if the state doesn't change from 2 levels above
				{
					Node* nextCall = depth(nextNode, level + 1, limit);

					if (nextCall != NULL)
						return nextCall;
				}
			}
		}
	}


	return NULL;
}

Node* iteDeepening(Node* currNode, int limit)
{
	Node* found;
	for (int level = 0; level < limit; level++)
	{
		found = depth(currNode, 0, level);

		if (found != NULL)
			return found;
	}

	return NULL;
}
   

Node* greedy(std::unordered_set<Node*, hashNode, hashNode>& tree, Node* currNode, int level, int limit, int heuristic)
{
	if (currNode == NULL || level >= limit)
	{
		return NULL;
	}

	if (DEBUG)
	{
		std::cout << *currNode << "\n\n";
	}

	Node* nextNode;

	std::priority_queue<Node*, std::vector<Node*>, sortH> nextRow;

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
					std::cout << "Level: " << level << "\n";
				}

				return nextNode;
			}

			if (tree.insert(nextNode).second)
			{
				nextNode->setH(heuristic);
				nextRow.push(nextNode);

				if (DEBUG)
				{
					std::cout << *nextNode << "\n\n";
				}
			}
		}
	}

	while (nextRow.size() > 0)
	{
		nextNode = nextRow.top();

		if (DEBUG)
		{
			std::cout << *nextNode << "\n\n";
		}
		
		Node* nextCall = greedy(tree, nextNode, level+1, limit, heuristic);

		if (nextCall != NULL)
			return nextCall;

		nextRow.pop();
	}


	return NULL;
}


Node* aStar(Node* currNode, int heuristic)
{
	std::multiset<Node*, sortF> openList;
	std::unordered_set<Node*, hashNode, hashNode> closedSet;
	
	openList.insert(currNode);

	Node* nextNode;

	std::multiset<Node*, sortF>::iterator it;

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

		closedSet.insert(currNode);

		if (DEBUG)
			std::cout << *currNode << "\n";

		for (int robotIndex = 0; robotIndex < currNode->state.size(); robotIndex++)
		{
			for (int i = 0; i < operations.size(); i++)
			{				
				nextNode = operations[i](currNode, robotIndex);
				nextNode->cost++;
				nextNode->parent = currNode;
				nextNode->operationName = operationNames[i];
				nextNode->setH(heuristic);
				
				if (DEBUG)
					std::cout << *nextNode << "\n";

				if (nextNode->state != currNode->state && closedSet.find(nextNode) == closedSet.end())
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

Node* aStar2(Node* currNode, int heuristic)
{
	std::multiset<Node*, sortF> openList;
	std::unordered_set<Node*, hashNode, hashNode> openSet;

	std::unordered_set<Node*, hashNode, hashNode> closedSet;

	openList.insert(currNode);
	openSet.insert(currNode);

	Node* nextNode;

	while (openList.size() > 0)
	{
		std::multiset<Node*, sortF>::iterator it = openList.begin();
		currNode = *(it);

		if (currNode->finished())
		{ 
			return currNode;
		}

		openList.erase(it);
		openSet.erase(currNode);

		closedSet.insert(currNode);

		if (DEBUG)
			std::cout << *currNode << "\n";

		for (int robotIndex = 0; robotIndex < currNode->state.size(); robotIndex++)
		{
			for (int i = 0; i < operations.size(); i++)
			{
				nextNode = operations[i](currNode, robotIndex);
				nextNode->cost++;
				nextNode->parent = currNode;
				nextNode->operationName = operationNames[i];
				nextNode->setH(heuristic);
				
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