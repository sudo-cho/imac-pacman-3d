#pragma once

#include <iostream>
#include <string>
#include <glm/glm.hpp>

#include <GL/glew.h>
#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

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
