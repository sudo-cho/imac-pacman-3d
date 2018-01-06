#pragma once

#include "mapobject.hpp"
#include "camera.hpp"

class Player : public MapObject{
private:
  int health;

public:
  Player(glm::vec2 pos, int dir);

  int getHealth();

  void takeDamage();
  void playerChangeDir(Camera);

  glm::vec2 position;
  glm::vec2 nextPos;
  int direction;
};
