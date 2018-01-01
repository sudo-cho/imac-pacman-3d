#include "mapobject.hpp"

using namespace std;

static int idObj = 0;

MapObject::MapObject(glm::vec2 pos, int dir, string t){
	id = idObj;
	idObj++;
	position = pos;
	direction = dir;
	type = t;
}

MapObject::~MapObject(){
}

