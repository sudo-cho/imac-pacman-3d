#pragma once

#include <glm/glm.hpp>

enum typeCase { empty = 0, path = 1, in = 2, out = 3};

class Case {
public:
	Case();
	Case(glm::vec2, int);
	~Case();
	glm::vec2 position;
	int type;
};