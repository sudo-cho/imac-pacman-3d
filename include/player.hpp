#pragma once

#include "mapobject.hpp"
#include "level.hpp"
#include "camera.hpp"

enum directionPlayer { NORD = 0, EST = 1, SUD = 2, OUEST = 3};

class Player : public MapObject{
private:
  int health;

public:
  Player(glm::vec2 pos, int dir);

  int getHealth();

  void takeDamage();
  void playerMove(Level,Camera);

  glm::vec2 position;
  int direction;
};
