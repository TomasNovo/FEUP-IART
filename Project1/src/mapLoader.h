#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include <vector>

#include "robot.h"
#include "node.h"

extern std::vector<std::vector<char>> map;

typedef Node* (*Operator)(Node*, int);

extern std::vector<Operator> operations;
extern std::vector<std::string> operationNames;

void initiateOperators();

bool validMove(Node* node, int robotIndex, int x, int y);

Node* initiateMap(std::string filename);

void loadMap(std::string filename, std::vector<Robot>& robots);

void initiateOperators();


#endif