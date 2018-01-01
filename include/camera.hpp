#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <glimac/common.hpp>
#include "level.hpp"

enum typeCamera { firstPerson = 0, thirdPerson = 1 };

class Camera {
public: 
	Camera();
	Camera(glm::vec2, int);
	~Camera();
	bool cameraChange(Level);
	
	glm::vec2 position;
	int currentState;
};