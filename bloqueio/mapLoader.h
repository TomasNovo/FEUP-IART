#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include <vector>
#include <functional>

#include "character.h"
#include "node.h"

extern std::vector<std::vector<char>> map;

typedef std::function<Node*(Node*, int)>  Operator;


extern std::vector<Operator> operations;
extern std::vector<std::string> operationNames;

void initiateOperators();

bool validMove(Node* node, int characterIndex, int x, int y);
bool validBar(Node* node, int characterIndex, std::string type, int i, int j);

Node* initiateMap();

void initiateOperators();

Node* doOperation(Node* currNode, int i, int characterIndex);

bool removeOperation(std::string operationName);


#endif