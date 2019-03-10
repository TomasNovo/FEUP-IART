#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

class Node
{
public:
	vector<int> state;
	
	int cost = 0;
	int level;
	double h = -1;
	double f;

	Node* parent = NULL;
	string operationName = "";

	Node();

	Node(int n);

	Node(const Node& node);

	void setH(vector<int> objective);
	
	bool operator==(const Node* node) const;
	bool operator==(const Node& node) const;

	// bool operator>(const Node* node) const;
	// bool operator>(const Node& node) const;

};

ostream& operator<<(ostream& os, const Node& node);


string printState(vector<int> state);


struct hashNode
{
	int operator() (const Node* node) const;

	bool operator() (const Node* node1, const Node* node2) const;
};

struct sortH
{
	bool operator() (const Node* node1, const Node* node2) const;
};

struct sortF
{
	bool operator() (const Node* node1, const Node* node2) const;
};

#endif