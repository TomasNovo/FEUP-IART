#include "mapLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>


vector<vector<int>> loadMap(string filename, vector<int>& robotPos, vector<int>& goalPos)
{
	ifstream ifs(filename);
	vector<vector<int>> map;
	string line, cell;
	int cellValue;

	robotPos.resize(0);
	goalPos.resize(0);

	while (getline(ifs, line))
	{
		if (line[0] >= '0' && line[0] <= '3')
		{
			if (line.back() != ',')
				line.push_back(',');

			stringstream ss(line);
			vector<int> row;
			for (int i = 0; getline(ss, cell, ','); ++i)
			{
				cellValue = cell[0] - '0';
								
				if (cellValue == 2)
				{
					robotPos.resize(2);
					robotPos[0] = row.size();
					robotPos[1] = map.size();
				}

				if (cellValue == 3)
				{
					goalPos.resize(2);
					goalPos[0] = row.size();
					goalPos[1] = map.size();
				} 

				row.push_back(cellValue);
			}

			map.push_back(row);
		}

	}

	if (robotPos.size() == 0)
	{
		cout << "Error getting robot position! robot position is character 2";
	}

	if (goalPos.size() == 0)
	{
		cout << "Error getting goal position! goal position is character 3";
	}

	return map;
}
