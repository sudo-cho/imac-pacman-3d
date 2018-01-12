#include <menu.hpp>

struct Vertex2DUV{
  glm::vec2 position, texcoords;
  Vertex2DUV(float x, float y, float u, float v);
};

Menu::Menu (GLuint t_tex, int t_nbButtons)
  : tex(t_tex), nbButtons(t_nbButtons)
{}

Menu::~Menu () {}

void Menu::drawMenu (GLuint locationMVPMatrix, GLuint locationMVMatrix, GLuint locationNormalMatrix, GLint uTexture, GLint uKd, GLint uKs, GLint uLightDir_vs, GLint uLightIntensity, GLint uIsTransparent ) {
  glBindVertexArray(this->vao);

  glm::mat4 MVMat = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -1.f));
  MVMat = glm::rotate(MVMat, 3.14159f, glm::vec3(0.f, 1.f, 0.f));
  MVMatrix = MVMat;

  glUniformMatrix4fv(locationMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
  glUniformMatrix4fv(locationMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
  glUniformMatrix4fv(locationNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

  glUniform1i(uIsTransparent, 1);
	glUniform3fv(uKd, 1, glm::value_ptr(glm::vec3(0,0,0)));
	glUniform3fv(uKs, 1, glm::value_ptr(glm::vec3(0,0,0)));
	glUniform3fv(uLightIntensity, 1, glm::value_ptr(glm::vec3(0,0,0)));
  glUniform3fv(uLightDir_vs, 1, glm::value_ptr(glm::vec3(0,0,0)));


  static const size_t TEXUNIT = 0;
  glUniform1i(uTexture, TEXUNIT);
  glActiveTexture(GL_TEXTURE0 + TEXUNIT);
  glBindTexture(GL_TEXTURE_2D, this->tex);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindTexture(GL_TEXTURE_2D, 0);
  glActiveTexture(GL_TEXTURE0);

  glBindVertexArray(0);

  for(int i = 0; i < nbButtons; ++i) {
    buttons[i].drawButton(locationMVPMatrix, locationMVMatrix, locationNormalMatrix, uTexture, uKd, uKs, uLightDir_vs, uLightIntensity, uIsTransparent);
  }

  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_SPACE]) {
    menuStatus = 1;
  }
}

void Menu::initQuadMenu (std::string text[]) {
  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

  static const Vertex2DUV vdata[] = {
    Vertex2DUV(-1.f, -1.f,  1, 1),
    Vertex2DUV( 1.f, -1.f,  0, 1),
    Vertex2DUV( -1.f, 1.f, 1, 0),
    Vertex2DUV( 1.f, 1.f, 0, 0)
  };

  glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(vdata), vdata, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(this->vao);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*)offsetof(Vertex2DUV, position));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*)offsetof(Vertex2DUV, texcoords));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  ProjMatrix = glm::perspective(glm::radians(90.f), 1.f, 0.1f, 100.f);
  NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

  // init buttons
  for (int i = 0; i < nbButtons; i++) {
    buttons.push_back(Button(text[i], texFromFile("assets/textures/menu/button.png"), i, nbButtons));
  }

}

void Menu::setTexture (const GLuint path) {
  this->tex = path;
}

int Menu::getMenuStatus() {
  return menuStatus;
}
