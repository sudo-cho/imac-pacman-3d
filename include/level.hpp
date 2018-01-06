#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "ghost.hpp"
#include "player.hpp"
#include "case.hpp"

class Level {
public:
	Level(std::string);
	~Level();
	void readImageFile(std::string);
	void createObjectFromLine(int,std::string);
	int width;
	int height;
	Case begin;
	Case out1;
	Case out2;
	std::vector<Case> map;
	std::vector<Ghost> ghosts;
	Case getCaseFromPos(glm::vec2);

	void moveObjects(Player *player);
};
