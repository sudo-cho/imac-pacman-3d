#pragma once

#include <string>
#include <GL/glew.h>
#include <vector>
#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <SDL2/SDL.h>
#include <texture.hpp>
#include <glimac/Image.hpp>

class Button {
  std::string text;
  GLuint tex{0};
  glm::mat4 ProjMatrix, MVPMatrix, MVMatrix, NormalMatrix;
  GLuint vbo, vao;

public:
  Button(std::string t_text, GLuint t_tex);
  ~Button();

  void initButton();
  void drawButton(GLuint locationMVPMatrix, GLuint locationMVMatrix, GLuint locationNormalMatrix, GLint uTexture);
};
