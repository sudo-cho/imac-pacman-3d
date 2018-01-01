#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "monster.hpp"
#include "case.hpp"

class Level {
public:
	Level(std::string);
	~Level();
	void printLevelTest();
	void readImageFile(std::string);
	void createObjectFromLine(int,std::string);
	int width;
	int height;
	int nbMonsters;
	Case begin;
	Case end;
	std::vector<Case> map;
	std::vector<Monster> monsters;
	Case getCaseFromPos(glm::vec2);
};