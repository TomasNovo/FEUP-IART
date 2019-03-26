#ifndef INTERFACE_H
#define INTERFACE_H

#include "node.h"
#include "ui_utilities.h"
#include "macros.h"
#include "algorithms.h"
#include <string>

using namespace std;


Node* play_loop(Node* currNode);

void info();

void agent(string map);

void agent_menu();

void agent_menu2();

int play();

int menu();

void walkingAnimation(Node* node1, Node* node2);

void printPath(Node* node);

void printMap(Node* node);

void printPath2(Node* node);

void printPath3(Node* node);


#endif