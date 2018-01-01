#include <objectcollectable.hpp>

using namespace std;

ObjectCollectable::ObjectCollectable(){
}

ObjectCollectable::ObjectCollectable(int typeO, int a, std::string n){
	if(typeO == gum) type = "gum";
	else if(typeO == supergum) type = "supergum";
	typeObj = typeO;
	amount = a;
	name = n;
}

ObjectCollectable::~ObjectCollectable(){
}