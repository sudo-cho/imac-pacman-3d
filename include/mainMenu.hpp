#pragma once

#include <menu.hpp>

class MainMenu : public Menu {
  int mainMenuStatus{0};

public:
  using Menu::Menu;

  void setMainMenuStatus(const int value);
  int getMainMenuStatus();
};
