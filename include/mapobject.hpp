#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <string>


class MapObject {
public:
	MapObject(glm::vec2,int,std::string);
	~MapObject();
	int id;
	glm::vec2 position;
	int direction;
	std::string type;

};
