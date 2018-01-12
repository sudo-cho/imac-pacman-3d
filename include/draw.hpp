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
#include "texture.hpp"

using namespace glimac;

struct Vertex2DUV{
  glm::vec2 position, texcoords;
  Vertex2DUV(float x, float y, float u, float v);
};

enum typeObjectSphere { PacmanSphere = 0 , ShadowSphere = 1 , SpeedySphere = 2 , BashfulSphere = 3 , PokeySphere = 4 ,  PacgumSphere = 5 , SuperPacgumSphere = 6};

class SphereDraw{
public:
  GLuint vbo, vao;
  glm::mat4 ProjMatrix, MVPMatrix, MVMatrix, NormalMatrix;
  static GLuint texPacman;
  static GLuint texShadow;
  static GLuint texSpeedy;
  static GLuint texBashful;
  static GLuint texPokey;
  static GLuint texGhostHunted;
  static GLuint texPacgum;
  static GLuint texSuperPacgum;
  static size_t refcount;

  SphereDraw(Sphere*);
  ~SphereDraw();

  void drawSphere(Sphere*, GLuint, GLuint, GLuint);
  void drawSphereObjects(Sphere*, GLuint, GLuint, GLuint, glm::mat4, GLint, int, int, GLint, GLint, GLint, GLint, GLint);
  void drawSphereObjects2(Sphere*, GLuint, GLuint, GLuint, glm::mat4, GLint, int, int, GLint, GLint, GLint, GLint, GLint);
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

  void drawWall(GLuint, GLuint, GLuint, glm::mat4, GLint, GLint, GLint, GLint, GLint, GLint);
  void drawPathWall(GLuint, GLuint, GLuint, glm::mat4, GLint, GLint, GLint, GLint, GLint, GLint);

};

class PathDraw{
public:
	PathDraw();
	~PathDraw();

	void drawPathFirstPerson(GLuint, GLuint, GLuint, Level, Player, GLint, GLint, GLint, GLint, GLint, GLint);
  void drawPathThirdPerson(GLuint, GLuint, GLuint, Level, Player, GLint, GLint, GLint, GLint, GLint, GLint);
};

