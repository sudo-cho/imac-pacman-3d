#include "game.hpp"

using namespace std;
using namespace glimac;

#ifdef _WIN32
#include <windows.h>
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
#else
  int main(int argc, char *argv[])
#endif
{
  Game game;

  bool _continue = true;
  while(_continue){
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        _continue = false;
      }
      game.render();
    }
  }
  return 0;
}
