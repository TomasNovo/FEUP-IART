#include "character.h"


Character::Character()
{
	coords = {-1,-1};
	objective = {-1,-1};
}

	
bool Character::finished()
{
	return (coords[0] == objective[0] || coords[1] == objective[1]);
}


bool Character::operator==(const Character& character) const
{
	return (this->coords == character.coords && this->objective == character.objective);
}

bool Character::operator<(const Character& character) const
{
	return (this->id < character.id);
}

std::ostream& operator<<(std::ostream& os, const Character& character)
{
	return (os << "[" << character.coords[0] << ", " << character.coords[1] << "] -> [" << character.objective[0] << ", " << character.objective[1] << "]");
}