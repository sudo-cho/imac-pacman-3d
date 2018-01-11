#include "case.hpp"

Case::Case(){
}

Case::Case(glm::vec2 pos, int t, int pac){
	position = pos;
	type = t;
	ifPacgum = pac;
}

Case::~Case(){
}