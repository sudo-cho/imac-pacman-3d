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
#include <math.h>

#include "entity.hpp"
#include "case.hpp"

enum typeGhostEnum { Shadow = 0 , Speedy = 1 , Bashful = 2 , Pokey = 3 };

class Ghost : public Entity{
public:
	Ghost(glm::vec2 pos, int dir, int type);
	~Ghost();
	glm::vec2 position;
	int typeGhost;
	glm::vec2 beginPos;
	glm::vec2 lastPos;

	void move (glm::vec2 posPlayer, int dirPlayer, std::vector<Case> mapLevel);
	void shadowMove(glm::vec2 posPlayer, std::vector<glm::vec2> possiblePos);
	void speedyMove(glm::vec2 posPlayer, int dirPlayer, std::vector<Case> mapLevel);
	void bashfulMove(glm::vec2 posPlayer, std::vector<glm::vec2> possiblePos);
	void pokeyMove(glm::vec2 posPlayer, std::vector<glm::vec2> possiblePos);

	void die();
	glm::vec2 getPos();
	Case getCaseFromMap(std::vector<Case> mapLevel, glm::vec2 pos);
	bool comparePos(glm::vec2 pos1, glm::vec2 pos2);
};
