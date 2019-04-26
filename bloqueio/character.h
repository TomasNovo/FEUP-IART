#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include <ostream>

class Character
{
public:
	std::vector<int> coords;
	std::vector<int> objective;

	std::vector<std::vector<int>> walls;

	char id;

	Character();
	
	bool finished();

	bool operator==(const Character& character) const;
	
	bool operator<(const Character& character) const;

	

};

std::ostream& operator<<(std::ostream& os, const Character& character);



#endif