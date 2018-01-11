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

enum typePacgum {gum = 0, supergum = 1};

class Pacgum {
public:
	Pacgum(glm::vec2 pos,int type);
	~Pacgum();
	glm::vec2 position;
	int typeObj;
};
