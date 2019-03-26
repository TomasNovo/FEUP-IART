#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include <vector>

#include "robot.h"

using namespace std;

vector<vector<char>> loadMap(string filename, vector<Robot>& robots);



#endif