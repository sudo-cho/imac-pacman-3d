#pragma once

#include <button.hpp>

class Menu {
  std::vector<Button> buttons;
  GLuint tex;
  int nbButtons;

public:
  Menu(GLuint t_tex, int t_nbButtons);
  ~Menu();

};
