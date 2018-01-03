#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "mapobject.hpp"
#include "typemonster.hpp"


class Monster : public MapObject {
public:
	Monster(glm::vec2,int,GLuint*,TypeMonster);
	~Monster();
	glm::vec2 move ();
	int changeDirection(int);
	void modifyHealth(int);
	int die();
	int attack();
	glm::vec2 getPos();
	int getDir();
	TypeMonster type;
	GLuint texture;
};
