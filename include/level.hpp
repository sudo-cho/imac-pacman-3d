#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "ghost.hpp"
#include "player.hpp"
#include "case.hpp"
#include "pacgum.hpp"

enum StateGame { pacmanHunted = 0 , pacmanAttack = 1 };

class Level {
public:
	Level(std::string);
	~Level();
	void readImageFile(std::string);
	int width;
	int height;
	Case begin;
	Case out1;
	Case out2;
	std::vector<Case> map;
	Ghost shadow;
	Ghost speedy;
	Ghost bashful;
	Ghost pokey;
	int statePacman;
	int superGumTimer;
	std::vector<Pacgum> pacgums;
	Case getCaseFromPos(glm::vec2);
	int getMapValueCase(glm::vec2);

	void moveObjects(Player *player);
	void playerContact(Player *player, Ghost ghost);
};
