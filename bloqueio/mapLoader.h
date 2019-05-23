#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include <vector>
#include <functional>
#include <random>
#include <chrono>

#include "character.h"
#include "node.h"

extern std::vector<std::vector<char>> map;

typedef std::function<Node*(Node*, int)>  Operator;
extern std::vector<Operator> operations;
extern std::vector<std::string> operationNames;

extern std::mt19937_64 rng;

void initiateOperators();

bool validMove(Node* node, int characterIndex, int x, int y);
bool validBar(Node* node, int characterIndex, std::string type, int i, int j);
bool validBarEfficient(Node* node, int characterIndex, std::string type, int i, int j, int maxCharacter);

Node* initiateMap(std::vector<char> characters);

void initiateOperators();

Node* doOperation(Node* currNode, int i, int characterIndex);
Node* doOperationEfficient(Node* currNode, int i, int characterIndex, int maxCharacter);
bool wallsCollide(std::string type1, int i1, int j1, std::string type2, int i2, int j2);

bool removeOperation(std::string operationName);


#endif