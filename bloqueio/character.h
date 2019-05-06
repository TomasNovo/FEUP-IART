#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include <ostream>
#include <set>

class Character
{
public:
	std::vector<int> coords;
	std::vector<int> objective;

	std::set<std::string> walls;

	char id;

	Character();
	
	bool finished();

	bool addWall(std::string wallName);

	int H();

	bool operator==(const Character& character) const;
	
	bool operator<(const Character& character) const;
};

std::ostream& operator<<(std::ostream& os, const Character& character);



#endif