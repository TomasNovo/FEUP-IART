#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>

#define BRDWDTH 7
#define BRDHGHT 6

using namespace std;

class Node
{
public:
	vector<vector<int>> state;

	int cost = 0;
	double h = 0;
	double f = 0;

	Node* parent = NULL;
	string operationName = "";

	Node();

	Node(const Node& node);

	void setH();

	int nlinhas4(int player);
	int checkWinFour(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

	int nlinhas3(int player);
	int checkWinThree(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

	int central(int player);

	bool play(int x);
	
	bool operator==(const Node* node) const;
	bool operator==(const Node& node) const;

	// bool operator>(const Node* node) const;
	// bool operator>(const Node& node) const;

};

ostream& operator<<(ostream& os, const Node& node);


string printState(vector<vector<int>> state);


struct hashNode
{
	int operator() (const Node* node) const;

	bool operator() (const Node* node1, const Node* node2) const;
};

struct sortH
{
	bool operator() (const Node* node1, const Node* node2) const;
};



#endif