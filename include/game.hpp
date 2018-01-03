#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/common.hpp>
#include <glimac/Sphere.hpp>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "typemonster.hpp"
#include "monster.hpp"
#include "level.hpp"
#include "draw.hpp"
#include "player.hpp"
#include "camera.hpp"

using namespace glimac;

class Game{
public:

  SDL_Window *window;
  SDL_GLContext glcontext;

  Game();
  ~Game();

  void initProgram(Program*, GLuint *, GLuint *, GLuint *, GLint *);

};

