#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>

#include "character.h"

class Node
{
public:
	std::vector<Character> state;
	
	int cost = 0;
	double h = -1;
	double f;

	Node* parent = NULL;
	std::string operationName = "";

	Node();

	Node(int n);

	Node(const Node& node);

	void setH(int heuristic);

	bool finished();
	
	bool operator==(const Node* node) const;
	bool operator==(const Node& node) const;

	// bool operator>(const Node* node) const;
	// bool operator>(const Node& node) const;

};

std::ostream& operator<<(std::ostream& os, const Node& node);


std::string printState(std::vector<Character> state);


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