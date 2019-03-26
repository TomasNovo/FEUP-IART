#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <unordered_set>
#include <set>
#include <queue>

#include "node.h"


Node* breadth(vector<Node*> currRow, int level);

Node* breadth2(unordered_set<Node*, hashNode, hashNode> tree, vector<Node*> currRow, int level);

Node* greedy(unordered_set<Node*, hashNode, hashNode>& tree, Node* currNode, int level);

multiset<Node*, sortF>::iterator linearSearchSet(multiset<Node*, sortF> input, Node* node);

Node* aStar(Node* currNode, int level);

Node* aStar2(Node* currNode, int level);


#endif