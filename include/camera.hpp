#pragma once

#include <GL/glew.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glimac/common.hpp>

enum typeCamera { firstPerson = 0, thirdPerson = 1 };

class Camera {
public:
  Camera(int);
  ~Camera();
  bool cameraChange();

  int currentState;
};
