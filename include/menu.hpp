#pragma once

#include <button.hpp>
#include <draw.hpp>

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

  void drawMenu (GLuint locationMVPMatrix, GLuint locationMVMatrix, GLuint locationNormalMatrix, GLint uTexture);
  void initQuadMenu();
  GLuint setTexture(const GLuint path);
  int getMenuStatus();
};
