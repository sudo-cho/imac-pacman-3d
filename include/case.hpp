#pragma once

#include <glm/glm.hpp>

enum typeCase { empty = 0, path = 1, in = 2, out = 3};
enum ifPacgum { noPacgum = 0, pacgum = 1, superPacgum = 2 };

class Case {
public:
	Case();
	Case(glm::vec2, int, int);
	~Case();
	glm::vec2 position;
	int type;
	int ifPacgum;
};