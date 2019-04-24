#include "robot.h"


Robot::Robot()
{
	coords = {-1,1};
	objective = {-1,-1};
}

	
bool Robot::finished()
{
	return (objective[0] == -1 && objective[1] == -1) ? true : (coords == objective);
}


bool Robot::operator==(const Robot& robot) const
{
	return (this->coords == robot.coords && this->objective == robot.objective);
}

bool Robot::operator<(const Robot& robot) const
{
	return (this->id < robot.id);
}

std::ostream& operator<<(std::ostream& os, const Robot& robot)
{
	return (os << "[" << robot.coords[0] << ", " << robot.coords[1] << "] -> [" << robot.objective[0] << ", " << robot.objective[1] << "]");
}