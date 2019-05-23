#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <unordered_set>
#include <set>
#include <queue>

#include "node.h"


Node* breadth(Node* currNode);

Node* depth(Node* currNode, int level, const int& limit);

Node* iteDeepening(Node* currNode, int limit);

Node* uniformCost(Node* currNode);

Node* greedy(std::unordered_set<Node*, hashNode, hashNode>& tree, Node* currNode, int level, int limit, int heuristic);

Node* aStar(Node* currNode, int heuristic);

Node* aStar2(Node* currNode, int heuristic);

Node* minimax(Node* currNode, int characterIndex, int depth, int heuristic);

#endif