#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "mapobject.hpp"
#include "case.hpp"

enum Direction { NORD = 0, EST = 1, SUD = 2, OUEST = 3};
enum typeGhostEnum { Shadow = 0 , Speedy = 1 , Bashful = 2 , Pokey = 3 };

class Ghost : public MapObject {
public:
	Ghost(glm::vec2,int,GLuint*,int);
	~Ghost();
	int typeGhost;
	glm::vec2 beginPos;

	void move (glm::vec2 posPlayer, int dirPlayer, std::vector<Case> mapLevel);
	void shadowMove(glm::vec2 posPlayer, int dirPlayer, std::vector<Case> mapLevel);
	void speedyMove(glm::vec2 posPlayer, int dirPlayer, std::vector<Case> mapLevel);
	void bashfulMove(glm::vec2 posPlayer, int dirPlayer, std::vector<Case> mapLevel);
	void pokeyMove(glm::vec2 posPlayer, int dirPlayer, std::vector<Case> mapLevel);

	int changeDirection(int);
	void die();
	glm::vec2 getPos();
	int getDir();
	GLuint texture;
};
