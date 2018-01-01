#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

enum typeObjectCollectable {gum = 0, supergum = 1};

class ObjectCollectable {
public:
	ObjectCollectable();
	ObjectCollectable(int,int,std::string);
	~ObjectCollectable();
	std::string type;
	int typeObj;
	int amount;
	std::string name;
};