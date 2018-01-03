#pragma once

#include <glimac/common.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Image.hpp>
#include <glimac/glm.hpp>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <SDL2/SDL.h>

#include "level.hpp"
#include "camera.hpp"
#include "player.hpp"

using namespace glimac;

struct Vertex2DUV{
  glm::vec2 position, texcoords;
  Vertex2DUV(float x, float y, float u, float v);
};

class ObjectDraw{
public:
  GLuint vbo, vao;

  ObjectDraw();

  void drawObject();
};

class SphereDraw{
public:
  GLuint vbo, vao;
  glm::mat4 ProjMatrix, MVPMatrix, MVMatrix, NormalMatrix;
  static GLuint texPacman;
  static size_t refcount;

  SphereDraw(Sphere*);
  ~SphereDraw();

  void drawSphere(Sphere*, GLuint, GLuint, GLuint);
  void drawPacman(Sphere*, GLuint, GLuint, GLuint, glm::mat4, GLint);
};

class WallDraw{
public:
  GLuint vbo, vao;
  glm::mat4 ProjMatrix, MVPMatrix, MVMatrix, NormalMatrix;
  static GLuint tex;
  static GLuint texP;
  static size_t refcount;

  WallDraw();
  ~WallDraw();

  void drawWall(GLuint, GLuint, GLuint, glm::mat4, GLint);
  void drawPathWall(GLuint, GLuint, GLuint, glm::mat4, GLint);

};

class PathDraw{
public:
	PathDraw();
	~PathDraw();

	void drawPathFirstPerson(GLuint, GLuint, GLuint, Level, Player, GLint);
  void drawPathThirdPerson(GLuint, GLuint, GLuint, Level, Player, GLint);
};

