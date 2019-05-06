#include "character.h"

//#include <cmath>


Character::Character()
{
	coords = {-1,-1};
	objective = {-1,-1};
}

	
bool Character::finished()
{
	return (coords[0] == objective[0] || coords[1] == objective[1]);
}

bool Character::addWall(std::string wallName)
{
	return walls.insert(wallName).second;
}

int Character::H()
{
	for (int i = 0; i < objective.size(); i++)
	{
		if (objective[i] == -1)
		{
			int j = (i + 1) % objective.size();

			return std::abs(coords[j] - objective[j]);
		}
	}

	return -1;
}

bool Character::operator==(const Character& character) const
{
	return (this->coords == character.coords && this->objective == character.objective && this->walls == character.walls);
}

bool Character::operator<(const Character& character) const
{
	return (this->id < character.id);
}

std::ostream& operator<<(std::ostream& os, const Character& character)
{
	return (os << "[" << character.coords[0] << ", " << character.coords[1] << "] -> [" << character.objective[0] << ", " << character.objective[1] << "]");
}