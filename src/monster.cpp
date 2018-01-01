#include "monster.hpp"

using namespace std;

enum Direction { N = 0, E = 1, S = 2, O = 3};

Monster::Monster(glm::vec2 pos, int dir, GLuint * tex, TypeMonster typeMons) : MapObject (pos,dir,"monster"){
	position = pos;
	direction = dir;
	if (tex != NULL) texture = *tex;
	type = typeMons;
}

Monster::~Monster(){
}

glm::vec2 Monster::move(){
	//animation
	if (direction == N){
		position.y += 1;
	}
	else if (direction == E){
		position.x += 1;
	}
	else if (direction){
		position.y -= 1;
	}
	else if(direction == O){
		position.x -= 1;
	}
	else {
		cout << "Error direction" << endl;
	}
	
	return position;
}

int Monster::changeDirection(int dir){
	if (dir == 0 || dir == 1 || dir == 2 || dir == 3){
		direction = dir;
	}
	else {
		cout << "Erreur mauvaise direction" << endl;
	}
	return direction;
}

void Monster::modifyHealth(int h){
	type.health -= h;
}

int Monster::die(){
	//animation
	return type.gold;
}

int Monster::attack(){
	//animation
	return type.force;
}

glm::vec2 Monster::getPos(){
	return position;
}

int Monster::getDir(){
	return direction;
}

