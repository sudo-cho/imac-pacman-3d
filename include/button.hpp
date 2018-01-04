#pragma once

#include <string>
#include <GL/glew.h>
#include <vector>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <glimac/Image.hpp>

static GLuint texFromFile(std::string path) {
  auto img = glimac::loadImage(path);
  GLuint tex = 0;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexImage2D(
               GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0,
               GL_RGBA, GL_FLOAT, img->getPixels()
               );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  return tex;
}

class Button {
  std::string text;
  GLuint tex{0};

public:
  Button(std::string t_text, GLuint t_tex);
  ~Button();
};
