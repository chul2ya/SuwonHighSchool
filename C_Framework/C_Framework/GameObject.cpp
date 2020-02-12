#include "pch.h"
#include "Room.h"

void GameObject::FileSave(FILE* fp)
{
	fprintf(fp, "%s %f %f \n", tag, position.x, position.y);
}

void GameObject::FileLoad(std::string buffer)
{
	std::string calc = strtok(NULL, " ");
	position.x += (float)atof(calc.c_str());

	calc = strtok(NULL, " ");
	position.y += (float)atof(calc.c_str());
}