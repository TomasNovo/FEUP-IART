#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include <vector>

#include "robot.h"
#include "node.h"

using namespace std;

extern vector<vector<char>> map;

typedef Node* (*Operator)(Node*, int);

extern vector<Operator> operations;
extern vector<string> operationNames;

void initiateOperators();

bool validMove(Node* node, int robotIndex, int x, int y);

Node* initiateMap(string filename);

void loadMap(string filename, vector<Robot>& robots);

void initiateOperators();


#endif