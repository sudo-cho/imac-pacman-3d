#include "ghost.hpp"

using namespace std;

Ghost::Ghost(glm::vec2 pos, int dir, GLuint * tex, int type) : MapObject (pos,dir,"ghost"){
	position = pos;
	direction = dir;
	if (tex != NULL) texture = *tex;
	typeGhost = type;
}

Ghost::~Ghost(){
}

void Ghost::move(glm::vec2 posPlayer, int dirPlayer, std::vector<Case> mapLevel){
	if(typeGhost == Shadow) shadowMove(posPlayer, dirPlayer, mapLevel);
	else if (typeGhost == Speedy) speedyMove(posPlayer, dirPlayer, mapLevel);
	else if (typeGhost == Bashful) bashfulMove(posPlayer, dirPlayer, mapLevel);
	else if (typeGhost == Pokey) pokeyMove(posPlayer, dirPlayer, mapLevel);
}

void Ghost::shadowMove(glm::vec2 posPlayer, int dirPlayer, std::vector<Case> mapLevel){
	/*if (player->position.y < this->position.y){

	}
	else {

	}
	if (player->direction == NORD){
		if (level->getCaseFromPos(glm::vec2(this->position.x, this->position.y -1)).type != 0) this->;
		else if (level->getCaseFromPos(glm::vec2(player->position.x, player->position.y -1)).type != 0)
	}
	else if (direction == EST) {
		if (level.getCaseFromPos(glm::vec2(position.x +1, position.y)).type != 0) nextPos = glm::vec2(position.x+1, position.y);
	}
	else if (direction == SUD) {
		if (level.getCaseFromPos(glm::vec2(position.x, position.y +1)).type != 0) nextPos = glm::vec2(position.x, position.y+1);
	}
	else if (direction == OUEST) {
		if (level.getCaseFromPos(glm::vec2(position.x -1, position.y)).type != 0) nextPos = glm::vec2(position.x-1, position.y);
	}*/
}

void Ghost::speedyMove(glm::vec2 posPlayer, int dirPlayer, std::vector<Case> mapLevel){

}

void Ghost::bashfulMove(glm::vec2 posPlayer, int dirPlayer, std::vector<Case> mapLevel){

}

void Ghost::pokeyMove(glm::vec2 posPlayer, int dirPlayer, std::vector<Case> mapLevel){

}

int Ghost::changeDirection(int dir){
	if (dir == 0 || dir == 1 || dir == 2 || dir == 3){
		direction = dir;
	}
	else {
		cout << "Erreur mauvaise direction" << endl;
	}
	return direction;
}

void Ghost::die(){

}

glm::vec2 Ghost::getPos(){
	return position;
}

int Ghost::getDir(){
	return direction;
}

