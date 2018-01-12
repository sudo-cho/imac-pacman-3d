#pragma once

#include <button.hpp>

class Menu {
  std::vector<Button> buttons;
  GLuint tex;
  int nbButtons;
  glm::mat4 ProjMatrix, MVPMatrix, MVMatrix, NormalMatrix;
  GLuint vbo, vao;
  int menuStatus{0};
public:
  Menu(GLuint t_tex, int t_nbButtons);
  ~Menu();

  void drawMenu (GLuint locationMVPMatrix, GLuint locationMVMatrix, GLuint locationNormalMatrix, GLint uTexture, GLint, GLint, GLint, GLint, GLint);
  void initQuadMenu(std::string text[]);
  void setTexture(const GLuint path);
  int getMenuStatus();
};
