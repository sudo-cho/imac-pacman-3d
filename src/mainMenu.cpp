//empty here
#include <mainMenu.hpp>

int MainMenu::getMainMenuStatus() {
  return mainMenuStatus;
}

void MainMenu::handleInputs () {
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_ESCAPE]) {
    if( mainMenuStatus == 0) {
      mainMenuStatus = 1;
    }
    else {
      mainMenuStatus = 0;
    }
  }
}
