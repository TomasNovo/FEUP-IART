#include "node.h"

using namespace std;


Node::Node()
{
	vector<int> row(BRDWDTH, 0);
	this->state = vector<vector<int>>(BRDHGHT, row);
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

void Node::setH()
{
	int currplayer = (this->cost % 2) + 1;
	int nextPlayer = ((this->cost+1) % 2) + 1;

	int fav1 = nlinhas4(currplayer) - nlinhas4(nextPlayer);
	int fav2 = 100*fav1 + nlinhas3(currplayer) - nlinhas3(nextPlayer);
	int fav3 = 100*fav1 + central(currplayer) - central(nextPlayer);
	int fav4 = 5*fav2 + fav3;

	this->h = fav3;

	this->f = this->cost + this->h;
}

int Node::nlinhas4(int player)
{
	int counter = 0;

	// Horizontal
	for (int i = 0; i < BRDHGHT; ++i)
	{
		for (int j = 0; j < BRDWDTH-3; ++j)
		{
			if (checkWinFour(j,i, j+1,i, j+2,i, j+3,i) == player)
				counter++;
		}
	}

	// Vertical
	for (int i = 0; i < BRDHGHT-3; ++i)
	{
		for (int j = 0; j < BRDWDTH; ++j)
		{
			if (checkWinFour(j,i, j,i+1, j,i+2, j,i+3) == player)
				counter++;
		}
	}

	// Down right
	for (int i = 0; i < BRDHGHT-3; ++i)
	{
		for (int j = 0; j < BRDWDTH-3; ++j)
		{
			if (checkWinFour(j,i, j+1,i+1, j+2,i+2, j+3,i+3) == player)
				counter++;
		}
	}

	// Down left
	for (int i = 0; i < BRDHGHT-3; ++i)
	{
		for (int j = 3; j < BRDWDTH; ++j)
		{
			if (checkWinFour(j,i, j-1,i+1, j-2,i+2, j-3,i+3) == player)
				counter++;
		}
	}


	return counter;
}

int Node::checkWinFour(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	if (this->state[y1][x1] != 0 && this->state[y1][x1] == this->state[y2][x2] && this->state[y1][x1] == this->state[y3][x3] && this->state[y1][x1] == this->state[y4][x4])
		return this->state[y1][x1];
	else
		return 0;
}


int Node::nlinhas3(int player)
{
	int counter = 0;

	// Horizontal
	for (int i = 0; i < BRDHGHT; ++i)
	{
		for (int j = 0; j < BRDWDTH-3; ++j)
		{
			if (checkWinThree(j,i, j+1,i, j+2,i, j+3,i) == player)
				counter++;
		}
	}

	// Vertical
	for (int i = 0; i < BRDHGHT-3; ++i)
	{
		for (int j = 0; j < BRDWDTH; ++j)
		{
			if (checkWinThree(j,i, j,i+1, j,i+2, j,i+3) == player)
				counter++;
		}
	}

	// Down right
	for (int i = 0; i < BRDHGHT-3; ++i)
	{
		for (int j = 0; j < BRDWDTH-3; ++j)
		{
			if (checkWinThree(j,i, j+1,i+1, j+2,i+2, j+3,i+3) == player)
				counter++;
		}
	}

	// Down left
	for (int i = 0; i < BRDHGHT-3; ++i)
	{
		for (int j = 3; j < BRDWDTH; ++j)
		{
			if (checkWinThree(j,i, j-1,i+1, j-2,i+2, j-3,i+3) == player)
				counter++;
		}
	}
	

	return counter;
}

int Node::checkWinThree(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	int pieces = 0;
	int spaces = 0;
	int first = this->state[y1][x1];

	if (this->state[y2][x2] == 0)
		spaces++;
	else if (this->state[y2][x2] != first)
		return 0;
	else
		pieces++;

	if (this->state[y3][x3] == 0)
		spaces++;
	else if (this->state[y3][x3] != first)
		return 0;
	else
		pieces++;

	if (this->state[y4][x4] == 0)
		spaces++;
	else if (this->state[y4][x4] != first)
		return 0;
	else
		pieces++;

	if (spaces == 1 && pieces == 3)
		return first;
	else
		return 0;
}

int Node::central(int player)
{
	int counter = 0;

	for (int i = 0; i < BRDHGHT; ++i)
	{
		if (this->state[i][4] == player)
			counter += 2;

		if (this->state[i][3] == player)
			counter++;

		if (this->state[i][5] == player)
			counter++;
	}

	return counter;
}

bool Node::play(int x)
{
	int i;
	for (i = 0; i < this->state.size() && this->state[i][x] == 0; ++i) // Finds free space
	{}
	i--;

	if (i == -1)
		return false;;

	this->state[i][x] = (this->cost % 2) + 1;

	this->cost++;
	this->setH();

	this->operationName = to_string(x);

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


ostream& operator<<(ostream& os, const Node& node)
{
	os << "Node {state=\n";
	for (int i = 0; i < node.state.size(); ++i)
	{
		os << "[";
		for (int j = 0; j < node.state[i].size(); ++j)
		{
			os << node.state[i][j];

			if (j != node.state[i].size()-1)
				os << ", ";
		}
		os << "],\n";
	}

	return (os << "cost = " << node.cost << "\n" << "h = "  << node.h << "\n");
}


string printState(vector<vector<int>> state)
{
	string foo = "";

	for (int i = 0; i < state.size(); ++i)
	{
		foo += "[";
		for (int j = 0; j < state[i].size(); ++j)
		{
			foo += to_string(state[i][j]);

			if (j != state[i].size()-1)
				foo += ", ";
		}
		foo += "],\n";
	}

	return foo;
}

int hashNode::operator() (const Node* node) const
{
	int hash = 0;

	for (int i = 0; i < node->state.size(); i++)
	{
		for (int j = 0; j < node->state[i].size(); j++)
		{
			hash += std::hash<int>()(node->state[i][j]);
		}
	}

	return static_cast<int>(std::hash<int>()(hash));
}

bool hashNode::operator() (const Node* node1, const Node* node2) const
{
	return (node1->state == node2->state);
}


bool sortH::operator() (const Node* node1, const Node* node2) const
{
	if (node1->f == node2->f)
	{
		for (int i = 0; i < node1->state.size(); ++i)
		{
			for (int j = 0; j < node1->state.size(); ++j)
			{
				if (node1->state[i][j] != node2->state[i][j])
					return (node1->state[i][j] < node2->state[i][j]);
			}
		}

		return false;
	}
	else
		return(node1->f < node2->f);
}

