#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <string>

enum Direction { NORD = 0, EST = 1, SUD = 2, OUEST = 3};

class Entity {
public:
	Entity(glm::vec2,int,std::string);
	~Entity();
	int id;
	glm::vec2 position;
	int direction;
	std::string type;

};
