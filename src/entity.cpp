#include "entity.hpp"

using namespace std;

static int idObj = 0;

Entity::Entity(){

}

Entity::Entity(glm::vec2 pos, int dir, string t){
	id = idObj;
	idObj++;
	position = pos;
	direction = dir;
	type = t;
}

Entity::~Entity(){
}

