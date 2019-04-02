#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <ostream>

class Robot
{
public:
	std::vector<int> coords;
	std::vector<int> objective;

	char id;

	Robot();
	
	bool finished();

	bool operator==(const Robot& robot) const;
	
	bool operator<(const Robot& robot) const;

};

std::ostream& operator<<(std::ostream& os, const Robot& robot);



#endif