#include "mapLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

vector<vector<char>> loadMap(string filename, vector<Robot>& robots)
{
	ifstream ifs(filename);
	vector<vector<char>> map;
	string line, cell;
	char cellValue;

	robots.resize(0);

	while (getline(ifs, line))
	{
		if (!((line[0] >= 'A' && line[0] <= 'Z') || (line[0] >= 'a' && line[0] <= 'z') || (line[0] >= '0' && line[0] <= '9')))
			continue;
	
		if (line.back() != ',')
			line.push_back(',');

		stringstream ss(line);
		vector<char> row = vector<char>();
		for (int i = 0; getline(ss, cell, ','); ++i)
		{
			cellValue = cell[0];

			if (!(cellValue >= '0' && cellValue <= '9')) // Not numeric 
			{
				char id;
				Robot robot;

				if (cellValue >= 'A' && cellValue <= 'Z') // Converts char to lower for id
					id = cellValue + ('a' - 'A');
				else
					id = cellValue;

				int index = -1;
				for (index = 0; index < robots.size() && robots[index].id != id; ++index) // Search robots for the same robot (equal id)
				{}

				if (index == robots.size())
				{
					robot = Robot();
					robot.id = id;
					robots.push_back(robot);
				}
				else
				{
					robot = robots[index];
				}

				if (cellValue >= 'a' && cellValue <= 'z') // Objective
				{
					robot.objective[0] = row.size();
					robot.objective[1] = map.size();
				}
				else if (cellValue >= 'A' && cellValue <= 'Z') // Robot
				{
					robot.coords[0] = row.size();
					robot.coords[1] = map.size();
				}

				robots[index] = robot;

				cellValue = '0';
			}

			row.push_back(cellValue);
		}

		map.push_back(row);
	}

	return map;
}
