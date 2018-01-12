//empty here
#include <mainMenu.hpp>

int MainMenu::getMainMenuStatus() {
  return mainMenuStatus;
}

void MainMenu::handleGlobalInputs () {
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  if (state[SDL_SCANCODE_ESCAPE]) {
    std::cout << mainMenuStatus << std::endl;
    if( mainMenuStatus == 0) {
      mainMenuStatus = 1;
    }
    else {
      mainMenuStatus = 0;
    }
    SDL_Delay(50);
  }
}
void MainMenu::handleInputs () {
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  if(state[SDL_SCANCODE_LEFT]) {

    std::cout << cursor << std::endl;
    if(cursor == 0) {}
    else {
      buttons[0].swapTexture();
      buttons[1].swapTexture();
      cursor = 0;
    }
    SDL_Delay(50);
  }

  if(state[SDL_SCANCODE_RIGHT]) {
    std::cout << cursor << std::endl;
    if(cursor == 1) {}
    else {
      buttons[0].swapTexture();
      buttons[1].swapTexture();
      cursor = 1;
    }
    SDL_Delay(50);
  }

  if (state[SDL_SCANCODE_SPACE]) {
    if (cursor == 0) {
      mainMenuStatus = 0;
    } else {
      exit(0);
    }
    SDL_Delay(50);
  }
}
