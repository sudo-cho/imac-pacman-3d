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


void Player::playerChangeDir(Camera camera){
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  
  if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]){
    if (camera.currentState == 1){
      direction = NORD;
      return;
    }
  }
  else if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]){
    if(camera.currentState == 1){
      direction = SUD;
      return;
    }
  }
  else if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]){
    if(camera.currentState == 1){
      direction = OUEST;
      return;
    }
  }
  else if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]){
    if(camera.currentState == 1){
      direction = EST;
      return;
    }
  }
  /*
  if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]){
    if (camera.currentState == 0){
      if (direction == NORD){
        if (level.getCaseFromPos(glm::vec2(position.x, position.y -1)).type != 0) nextPos = glm::vec2(position.x, position.y-1);
      }
      else if (direction == EST) {
        if (level.getCaseFromPos(glm::vec2(position.x +1, position.y)).type != 0) nextPos = glm::vec2(position.x+1, position.y);
      }
      else if (direction == SUD) {
        if (level.getCaseFromPos(glm::vec2(position.x, position.y +1)).type != 0) nextPos = glm::vec2(position.x, position.y+1);
      }
      else if (direction == OUEST) {
        if (level.getCaseFromPos(glm::vec2(position.x -1, position.y)).type != 0) nextPos = glm::vec2(position.x-1, position.y);
      }
    }
    else {
      if (level.getCaseFromPos(glm::vec2(position.x, position.y -1)).type != 0) nextPos = glm::vec2(position.x, position.y-1);
      direction = NORD;
    }
  }
  else if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]){
    if(camera.currentState == 0){
      if (direction == NORD){
        if (level.getCaseFromPos(glm::vec2(position.x, position.y +1)).type != 0) position.y += 1;
      }
      else if (direction == EST) {
        if (level.getCaseFromPos(glm::vec2(position.x -1, position.y)).type != 0) position.x -= 1;
      }
      else if (direction == SUD) {
        if (level.getCaseFromPos(glm::vec2(position.x, position.y -1)).type != 0) position.y -= 1;
      }
      else if (direction == OUEST) {
        if (level.getCaseFromPos(glm::vec2(position.x +1, position.y)).type != 0) position.x += 1;
      }
      SDL_Delay(150);
    }
    else {
      if (level.getCaseFromPos(glm::vec2(position.x, position.y +1)).type != 0) position.y += 1;
      direction = SUD;
      SDL_Delay(100);
    }
  }
  else if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]){
    if(camera.currentState == 0){
      if (direction == NORD){
        if (level.getCaseFromPos(glm::vec2(position.x -1, position.y)).type != 0) position.x -= 1;
      }
      else if (direction == EST) {
        if (level.getCaseFromPos(glm::vec2(position.x, position.y -1)).type != 0) position.y -= 1;
      }
      else if (direction == SUD) {
        if (level.getCaseFromPos(glm::vec2(position.x +1, position.y)).type != 0) position.x += 1;
      }
      else if (direction == OUEST) {
        if (level.getCaseFromPos(glm::vec2(position.x, position.y +1)).type != 0) position.y += 1;
      }
      SDL_Delay(150);
    }
    else {
      if (level.getCaseFromPos(glm::vec2(position.x -1, position.y)).type != 0) position.x -= 1;
      direction = OUEST;
      SDL_Delay(100);
    }
  }
  else if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]){
    if(camera.currentState == 0){
      if (direction == NORD){
        if (level.getCaseFromPos(glm::vec2(position.x +1, position.y)).type != 0) position.x += 1;
      }
      else if (direction == EST) {
        if (level.getCaseFromPos(glm::vec2(position.x, position.y +1)).type != 0) position.y += 1;
      }
      else if (direction == SUD) {
        if (level.getCaseFromPos(glm::vec2(position.x -1, position.y)).type != 0) position.x -= 1;
      }
      else if (direction == OUEST) {
        if (level.getCaseFromPos(glm::vec2(position.x, position.y -1)).type != 0) position.y -= 1;
      }
      SDL_Delay(150);
    }
    else {
      if (level.getCaseFromPos(glm::vec2(position.x +1, position.y)).type != 0) position.x += 1;
      direction = EST;
      SDL_Delay(100);
    }
  }
  // CLAVIER TOUCHE A
  else if (state[SDL_SCANCODE_Q]){
    if (camera.currentState == 0){
      if (direction == 0) direction = 3;
      else direction--;
      SDL_Delay(150);
    }
  }
  // CLAVIER TOUCHE E
  else if (state[SDL_SCANCODE_E]){
    if (camera.currentState == 0){
      if (direction == 3) direction = 0;
      else direction++;
      SDL_Delay(150);
    }
  }
  */
}
