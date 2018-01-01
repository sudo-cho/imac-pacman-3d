#include "typemonster.hpp"

using namespace std;

TypeMonster::TypeMonster(){
}

TypeMonster::TypeMonster(string nameMons, int h, int g, int f){
	if (nameMons.find("jack")) idType = jack;
	else if (nameMons.find("girl")) idType = girl;
	else if (nameMons.find("mom")) idType = mom;
	name = nameMons;
	health = h;
	gold = g;
	force = f;
}
