#include <menu.hpp>

Menu::Menu (GLuint t_tex, int t_nbButtons)
  : tex(t_tex), nbButtons(t_nbButtons)
{
  for (int i = 0; i < t_nbButtons; i++) {
    buttons.push_back(Button("bonjour", texFromFile("assets/textures/murSimple.png")));
  }
}

Menu::~Menu () {}
