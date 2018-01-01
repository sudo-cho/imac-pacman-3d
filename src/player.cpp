#include "player.hpp"

Player::Player(glm::vec2 pos, int dir) : MapObject (pos,dir,"player")
{
	health = 3;
  position = pos;
  direction = dir;
	id++;
}

void Player::takeDamage(){
  health--;
}

int Player::getHealth(){
  return this->health;
}


void Player::playerMove(Level level){
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  
  if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]){
    if (direction == NORD){
      if (level.getCaseFromPos(glm::vec2(position.x, position.y -1)).type == 1) position.y -= 1;
    }
    else if (direction == EST) {
      if (level.getCaseFromPos(glm::vec2(position.x +1, position.y)).type == 1) position.x += 1;
    }
    else if (direction == SUD) {
      if (level.getCaseFromPos(glm::vec2(position.x, position.y +1)).type == 1) position.y += 1;
    }
    else if (direction == OUEST) {
      if (level.getCaseFromPos(glm::vec2(position.x -1, position.y)).type == 1) position.x -= 1;
    }
    SDL_Delay(150);
  }
  else if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]){
    if (direction == NORD){
      if (level.getCaseFromPos(glm::vec2(position.x, position.y +1)).type == 1) position.y += 1;
    }
    else if (direction == EST) {
      if (level.getCaseFromPos(glm::vec2(position.x -1, position.y)).type == 1) position.x -= 1;
    }
    else if (direction == SUD) {
      if (level.getCaseFromPos(glm::vec2(position.x, position.y -1)).type == 1) position.y -= 1;
    }
    else if (direction == OUEST) {
      if (level.getCaseFromPos(glm::vec2(position.x +1, position.y)).type == 1) position.x += 1;
    }
    SDL_Delay(150);
  }
  else if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]){
    if (direction == NORD){
      if (level.getCaseFromPos(glm::vec2(position.x -1, position.y)).type == 1) position.x -= 1;
    }
    else if (direction == EST) {
      if (level.getCaseFromPos(glm::vec2(position.x, position.y -1)).type == 1) position.y -= 1;
    }
    else if (direction == SUD) {
      if (level.getCaseFromPos(glm::vec2(position.x +1, position.y)).type == 1) position.x += 1;
    }
    else if (direction == OUEST) {
      if (level.getCaseFromPos(glm::vec2(position.x, position.y +1)).type == 1) position.y += 1;
    }
    SDL_Delay(150);
  }
  else if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]){
    if (direction == NORD){
      if (level.getCaseFromPos(glm::vec2(position.x +1, position.y)).type == 1) position.x += 1;
    }
    else if (direction == EST) {
      if (level.getCaseFromPos(glm::vec2(position.x, position.y +1)).type == 1) position.y += 1;
    }
    else if (direction == SUD) {
      if (level.getCaseFromPos(glm::vec2(position.x -1, position.y)).type == 1) position.x -= 1;
    }
    else if (direction == OUEST) {
      if (level.getCaseFromPos(glm::vec2(position.x, position.y -1)).type == 1) position.y -= 1;
    }
    SDL_Delay(150);
  }
  // CLAVIER TOUCHE A
  else if (state[SDL_SCANCODE_Q]){
    if (direction == 0) direction = 3;
    else direction--;
    SDL_Delay(150);
  }
  // CLAVIER TOUCHE E
  else if (state[SDL_SCANCODE_E]){
    if (direction == 3) direction = 0;
    else direction++;
    SDL_Delay(150);
  }
}
