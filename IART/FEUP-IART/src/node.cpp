#include "node.h"

#include <cmath>
#include <sstream>


Node::Node()
{

}


Node::Node(const Node& node)
{
	this->state = node.state;

	this->cost = node.cost;
	this->h = node.h;

	this->parent = node.parent;
	this->operationName = node.operationName;
}

void Node::setH()
{
	this->h = 0;

	for (int i = 0; i < state.size(); ++i)
	{
		if (state[i].objective[0] == -1 && state[i].objective[1] == -1)
			continue;
		
		int deltaX = abs(state[i].coords[0] - state[i].objective[0]), deltaY = abs(state[i].coords[1] - state[i].objective[1]);
		this->h += (deltaX + deltaY)/(double)16;
	}

	this->f = this->cost + this->h;
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


std::string printState(std::vector<Robot> state)
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
		// hash += std::hash<int>()(node->state[i].objective[0]);
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


