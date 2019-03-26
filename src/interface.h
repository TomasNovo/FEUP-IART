#ifndef INTERFACE_H
#define INTERFACE_H

#include "node.h"
#include "ui_utilities.h"
#include "macros.h"

using namespace std;


Node* play_loop(Node* currNode);

int play();

int menu();

void walkingAnimation(Node* node1, Node* node2);

void printPath(Node* node);

void printMap(Node* node);

void printPath2(Node* node);

void printPath3(Node* node);


#endif