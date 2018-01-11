#include "game.hpp"

using namespace glimac;

Game::Game ()
  : level(Level((std::string)"assets/level1.dml"))
  , camera(Camera(1))
  , player(Player(glm::vec2(level.begin.position.x, level.begin.position.y), 3))
  , smenu(StartMenu(0, 1))
{
  this->initWindow();
  this->initProgram();
  this->initMenu();
}

Game::~Game () {
  SDL_GL_DeleteContext(glcontext);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

bool Game::initWindow () {
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "SDL_Init(): " << SDL_GetError() << std::endl;
    return false;
  }
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  window = SDL_CreateWindow("PACIMAC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    printf("Could not create window: %s\n", SDL_GetError());
  }

  glcontext = SDL_GL_CreateContext(window);

  GLint error;
  if(GLEW_OK != (error = glewInit())) {
    std::cerr << "Could not initialize Glew" << std::endl;
  }

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::cout << "GLEW " << glewGetString(GLEW_VERSION) << std::endl;
  std::cout << glGetString(GL_VERSION) << std::endl;

  return true;
}

void Game::initProgram () {
  Program program = loadProgram("assets/shaders/3D.vs.glsl", "assets/shaders/normals.fs.glsl");
  program.use();

  locationMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
  locationMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
  locationNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
  uTexture = glGetUniformLocation(program.getGLId(), "uTexture");
}
void Game::render () {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (smenu.getMenuStatus() == 0) {
    smenu.drawMenu(locationMVPMatrix, locationMVMatrix, locationNormalMatrix, uTexture);
  }
  else {
    if (!camera.cameraChange()) {
      player.playerChangeDir(camera);
      level.moveObjects(&player);
      // SDL_Delay(100);
    }

    if (camera.currentState == 0){
      path.drawPathFirstPerson(locationMVPMatrix, locationMVMatrix, locationNormalMatrix, level, player, uTexture);
    }
    else {
      path.drawPathThirdPerson(locationMVPMatrix, locationMVMatrix, locationNormalMatrix, level, player, uTexture);
    }
  }

  SDL_Delay(1000/60);
  SDL_GL_SwapWindow(window);
}

void Game::initMenu () {
  smenu.setTexture(texFromFile("assets/textures/menu/startmenu.png"));
  smenu.initQuadMenu();
}
