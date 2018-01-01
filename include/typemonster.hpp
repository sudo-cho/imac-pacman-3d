#pragma once

#include <iostream>
#include <string>

enum typeMonster {jack = 0, girl = 1, mom = 2};

class TypeMonster {
public:
	TypeMonster(std::string,int,int,int);
	TypeMonster();
	int idType;
	std::string name;
	int health;
	int gold;
	int force;

};
