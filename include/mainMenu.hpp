#pragma once

#include <menu.hpp>

class MainMenu : public Menu {
  int mainMenuStatus{0};

public:
  using Menu::Menu;

  int getMainMenuStatus();
  void handleInputs();
};
