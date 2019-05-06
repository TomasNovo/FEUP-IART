#include "node.h"

#include <cmath>
#include <sstream>

#include "macros.h"
#include  "mapLoader.h"

Node::Node()
{
	Character character;

	character.coords[0] = 4;
	character.coords[1] = 0;
	character.objective[1] = 8;
	character.id = 'a';
	state.push_back(character);

	character.coords[0] = 8;
	character.coords[1] = 4;
	character.objective[0] = 0;
	character.id = 'b';
	state.push_back(character);

	character.coords[0] = 4;
	character.coords[1] = 8;
	character.objective[1] = 0;
	character.id = 'c';
	state.push_back(character);

	character.coords[0] = 0;
	character.coords[1] = 4;
	character.objective[0] = 8;
	character.id = 'd';
	state.push_back(character);
}


Node::Node(const Node& node)
{
	this->state = node.state;

	this->cost = node.cost;
	this->h = node.h;
	this->f = node.f;

	this->parent = node.parent;
	this->operationName = node.operationName;
}

void Node::setH(int heuristic)
{
	this->h = 0;

	// h is sorthest distance to border subtracted distances of other players.

	for (size_t i = 0; i < state.size(); i++)
	{
		int characterH = getDistance(i);

		if (i == 0)
			this->h -= characterH;
		else
			this->h += characterH;
	}
	
	this->f = this->cost + this->h;
}


int Node::getDistance(int characterIndex)
{
	Node* currNode = new Node(*this);
	Node* nextNode;

	std::multiset<Node*, sortF> openList;
	std::unordered_set<Node*, hashNode, hashNode> openSet;

	std::unordered_set<Node*, hashNode, hashNode> closedSet;

	openList.insert(currNode);
	openSet.insert(currNode);

	while (openList.size() > 0)
	{
		std::multiset<Node*, sortF>::iterator it = openList.begin();
		currNode = *(it);

		if (currNode->state[characterIndex].finished())
		{
			int result = currNode->cost - this->cost;

			// Erase nodes
			for (auto ite = openList.begin(); ite != openList.end(); ++ite)
				delete *ite;

			for (auto ite = closedSet.begin(); ite != closedSet.end(); ++ite)
				delete *ite;

			return result;
		}

		openList.erase(it);
		openSet.erase(currNode);

		closedSet.insert(currNode);

		if (DEBUG)
			std::cout << *currNode << "\n";

		for (int i = 0; i < 4; i++)
		{
			nextNode = operations[i](currNode, characterIndex);
			nextNode->cost++;
			nextNode->h = nextNode->state[characterIndex].H();
			nextNode->f = nextNode->cost + nextNode->h;

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
						Node* itNode = (*it);

						openList.erase(*it);
						openSet.erase(*it);

						delete itNode;

						openList.insert(nextNode);
						openSet.insert(nextNode);
					}
				}
			}
			else
				delete nextNode;
		}
	}

	return -1;
}



bool Node::finished()
{
	for (int i = 0; i < state.size(); ++i)
	{
		if (!state[i].finished())
			return false;
	}

	return true;
}


bool Node::operator==(const Node* node) const
{
	return (this->state == node->state);
}

bool Node::operator==(const Node& node) const
{
	return (this->state == node.state);
}

// bool Node::operator>(const Node* node) const
// {
// 	return (this->h < node->h);
// }

// bool Node::operator>(const Node& node) const
// {
// 	return (this->h < node.h);
// }


std::ostream& operator<<(std::ostream& os, const Node& node)
{
	return (os << "Node {state=\n" << printState(node.state) << "cost = " << node.cost << "\n" << "h = "  << node.h << "\n");
}


std::string printState(std::vector<Character> state)
{
	std::stringstream ss;
	for (int i = 0; i < state.size(); ++i)
	{
		ss << state[i] << "\n";
	}

	ss << "\n";

	return ss.str();
}

int hashNode::operator() (const Node* node) const
{
	int hash = 0;

	for (int i = 0; i < node->state.size(); ++i)
	{
		hash += std::hash<int>()(node->state[i].coords[0]);
		hash += std::hash<int>()(node->state[i].coords[1]);
		// hash += std::hash<int>()(node->state[i].objective[0]);\
		// hash += std::hash<int>()(node->state[i].objective[1]);
	}

	return static_cast<int>(std::hash<int>()(hash));
}

bool hashNode::operator() (const Node* node1, const Node* node2) const
{
	return (node1->state == node2->state);
}

bool sortH::operator() (const Node* node1, const Node* node2) const
{
	if (node1->h == node2->h)
	{
		for (int i = 0; i < node1->state.size(); ++i)
		{
			for (int j = 0; j < node1->state[i].coords.size(); ++j)
			{
				if (node1->state[i].coords[j] != node2->state[i].coords[j])
					return (node1->state[i].coords[j] > node2->state[i].coords[j]);
			}
		}

		return false;
	}
	else
	{
		return (node1->h > node2->h);
	}
}

bool sortF::operator() (const Node* node1, const Node* node2) const
{
	return (node1->f < node2->f);
}


