#pragma once

#include "entity.hpp"
#include "camera.hpp"
#include "hud.hpp"

class Player : public Entity{
private:
  int health;

public:
  Player(glm::vec2 pos, int dir);

  int getHealth();

  void takeDamage(Hud &hud);
  void playerChangeDir(Camera &camera);

  glm::vec2 position;
  glm::vec2 nextPos;
  glm::vec2 beginPos;
  int direction;
  int nbMoves;
  int score;
};
