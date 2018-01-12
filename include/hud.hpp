#pragma once

#include <vector>
#include <texture.hpp>

#include <SDL2/SDL.h>


class Heart {
  glm::mat4 ProjMatrix, MVPMatrix, MVMatrix, NormalMatrix;
  GLuint vbo, vao;
  int pos;
  GLuint tex;
public:
  Heart(const int pos, GLuint tex);
  ~Heart();

  void initHeart();
  void drawHeart(GLuint locationMVPMatrix, GLuint locationMVMatrix, GLuint locationNormalMatrix, GLint uTexture);
};

class Hud {
public:
  Hud();
  ~Hud();

  void initHearts();
  void removeHeart();

  std::vector<Heart> hearts;
};
