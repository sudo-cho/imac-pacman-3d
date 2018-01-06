#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/common.hpp>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "ghost.hpp"
#include "level.hpp"
#include "draw.hpp"
#include "player.hpp"
#include "camera.hpp"

using namespace glimac;

class Game{
  GLuint locationMVPMatrix = 0, locationMVMatrix = 0, locationNormalMatrix = 0;
  GLint uTexture = 0;
  SDL_Window * window;
  SDL_GLContext glcontext;
  Level level;
  Camera camera;
  Player player;
  PathDraw path;
public:
  Game();
  ~Game();

  bool initWindow();
  void initProgram();
  void render();
};
