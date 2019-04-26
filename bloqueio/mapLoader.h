#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include <vector>

#include "character.h"
#include "node.h"

extern std::vector<std::vector<char>> map;

typedef Node* (*Operator)(Node*, int);

extern std::vector<Operator> operations;
extern std::vector<std::string> operationNames;

void initiateOperators();

bool validMove(Node* node, int characterIndex, int x, int y);

Node* initiateMap();

void loadMap(std::string filename, std::vector<Character>& characters);

void initiateOperators();


#endif