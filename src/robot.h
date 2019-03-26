#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <ostream>

using namespace std;

class Robot
{
public:
	vector<int> coords;
	vector<int> objective;

	char id;

	Robot();
	
	bool finished();

	bool operator==(const Robot* robot) const;
	bool operator==(const Robot& robot) const;
};

ostream& operator<<(ostream& os, const Robot& robot);



#endif