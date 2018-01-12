#include "player.hpp"

Player::Player(glm::vec2 pos, int dir) : Entity (pos,dir,"player") {
  health = 3;
  position = pos;
  direction = dir;
  nbMoves = 0;
  score = 0;
  beginPos = pos;
  id++;

}

void Player::takeDamage(Hud &hud){
  health--;
  hud.removeHeart();
}

int Player::getHealth(){
  return this->health;
}


void Player::playerChangeDir(Camera &camera){
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]){
    if (camera.currentState == 1){
      direction = NORD;
      nbMoves++;
      return;
    }
  }
  else if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]){
    if (camera.currentState == 1){
      direction = SUD;
      nbMoves++;
      return;
    }
    else {
      if (direction == NORD) { direction = SUD; }
      else if (direction == SUD) { direction = NORD; }
      else if (direction == OUEST) { direction = EST; }
      else if (direction == EST) { direction = OUEST; }
      nbMoves++;
    }
  }
  else if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]){
    if (camera.currentState == 1){
      direction = OUEST;
      nbMoves++;
      return;
    }
    else {
      if (direction == NORD) { direction = OUEST; }
      else if (direction == SUD) { direction = EST; }
      else if (direction == OUEST) { direction = SUD; }
      else if (direction == EST) { direction = NORD; }
      nbMoves++;
    }
  }
  else if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]){
    if (camera.currentState == 1){
      direction = EST;
      nbMoves++;
      return;
    }
    else {
      if (direction == NORD) { direction = EST; }
      else if (direction == SUD) { direction = OUEST; }
      else if (direction == OUEST) { direction = NORD; }
      else if (direction == EST) { direction = SUD; }
      nbMoves++;
    }
  }
}
