#include "ghost.hpp"

using namespace std;

Ghost::Ghost(glm::vec2 pos, int dir, int type)  : Entity (pos,dir,"ghost") {
	position = pos;
	typeGhost = type;
	beginPos = glm::vec2(10,8);
}

Ghost::~Ghost(){
}

void Ghost::move(glm::vec2 posPlayer, int dirPlayer, std::vector<Case> mapLevel){

	std::vector<glm::vec2> possiblePositions;
	glm::vec2 posNorth = glm::vec2(position.x, position.y -1);
	glm::vec2 posSouth = glm::vec2(position.x, position.y +1);
	glm::vec2 posEast = glm::vec2(position.x +1, position.y);
	glm::vec2 posWest = glm::vec2(position.x -1, position.y);

	if (getCaseFromMap(mapLevel,posNorth).type != 0 && !comparePos(posNorth,lastPos)) possiblePositions.push_back(posNorth);
	if (getCaseFromMap(mapLevel,posSouth).type != 0 && !comparePos(posSouth,lastPos)) possiblePositions.push_back(posSouth);
	if (getCaseFromMap(mapLevel,posEast).type != 0 && !comparePos(posEast,lastPos)) possiblePositions.push_back(posEast);
	if (getCaseFromMap(mapLevel,posWest).type != 0 && !comparePos(posWest,lastPos)) possiblePositions.push_back(posWest);

	if (possiblePositions.size() == 1){
		lastPos = glm::vec2(position.x,position.y);
		position.x = possiblePositions[0].x;
		position.y = possiblePositions[0].y;
	}
	else {
		if(typeGhost == Shadow) shadowMove(posPlayer, possiblePositions);
		else if (typeGhost == Speedy) speedyMove(posPlayer, dirPlayer, mapLevel);
		else if (typeGhost == Bashful) bashfulMove(posPlayer, possiblePositions);
		else if (typeGhost == Pokey) pokeyMove(posPlayer, possiblePositions);
	}
	
}

void Ghost::shadowMove(glm::vec2 posPlayer, std::vector<glm::vec2> possiblePos){
	if (possiblePos.size() == 0) possiblePos.push_back(lastPos);
	glm::vec2 bestPos = possiblePos[0];
	for (int i = 1 ; i < (int)possiblePos.size() ; i++){
		if (pow((possiblePos[i].x - posPlayer.x),2) + pow((possiblePos[i].y - posPlayer.y),2) < pow((bestPos.x - posPlayer.x),2) + pow((bestPos.y - posPlayer.y),2)){
			bestPos = possiblePos[i];
		}
	}
	lastPos = glm::vec2(position.x,position.y);
	position.x = bestPos.x;
	position.y = bestPos.y;
}

void Ghost::speedyMove(glm::vec2 posPlayer, int dirPlayer, std::vector<Case> mapLevel){

}

void Ghost::bashfulMove(glm::vec2 posPlayer, std::vector<glm::vec2> possiblePos){
	//possiblePos.push_back(lastPos);
	glm::vec2 bestPos = possiblePos[0];
	for (int i = 1 ; i < (int)possiblePos.size() ; i++){
		if (pow((possiblePos[i].x - posPlayer.x) + (possiblePos[i].y - posPlayer.y),2) < pow((bestPos.x - posPlayer.x) + (bestPos.y - posPlayer.y),2)){
			bestPos = possiblePos[i];
		}
	}
	lastPos = glm::vec2(position.x,position.y);
	position.x = bestPos.x;
	position.y = bestPos.y;
}

void Ghost::pokeyMove(glm::vec2 posPlayer, std::vector<glm::vec2> possiblePos){
	if (possiblePos.size() == 0) possiblePos.push_back(lastPos);
	glm::vec2 bestPos = possiblePos[rand() % (int)possiblePos.size()];
	lastPos = glm::vec2(position.x,position.y);
	position.x = bestPos.x;
	position.y = bestPos.y;
}

void Ghost::die(){

}

glm::vec2 Ghost::getPos(){
	return position;
}

Case Ghost::getCaseFromMap(std::vector<Case> mapLevel, glm::vec2 pos){
	Case caseNull;
	for (int n=0 ; n < (int)mapLevel.size() ; n++){
		if (mapLevel[n].position.x == pos.x && mapLevel[n].position.y == pos.y) return mapLevel[n];
	}
	return caseNull;
}

bool Ghost::comparePos(glm::vec2 pos1, glm::vec2 pos2){
	if (pos1.x == pos2.x && pos1.y == pos2.y) return true;
	else return false;
}