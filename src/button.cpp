#include <button.hpp>

struct Vertex2DUV{
  glm::vec2 position, texcoords;
  Vertex2DUV(float x, float y, float u, float v);
};

Button::Button (std::string t_text, GLuint t_tex, GLuint t_texS, int t_pos, int nbButtons)
  : text(t_text), tex(t_tex), texS(t_texS), m_pos(t_pos), nbButtons(nbButtons)
{
  cursor = m_pos;
  this->initButton();
}

Button::~Button () {}

void Button::initButton () {
  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

  static const Vertex2DUV vdata[] = {
    Vertex2DUV(-0.15f, -0.15f,  1, 1),
    Vertex2DUV( 0.15f, -0.15f,  0, 1),
    Vertex2DUV( -0.15f, 0.15f, 1, 0),
    Vertex2DUV( 0.15f, 0.15f, 0, 0)
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
}

void Button::drawButton (GLuint locationMVPMatrix, GLuint locationMVMatrix, GLuint locationNormalMatrix, GLint uTexture, GLint uKd, GLint uKs, GLint uLightDir_vs, GLint uLightIntensity, GLint uIsTransparent) {
  glBindVertexArray(this->vao);

  glm::mat4 MVMat;
  if (m_pos == 0 && nbButtons == 1) {
    MVMat = glm::translate(glm::mat4(1.f), glm::vec3(0.f, -0.14f, -0.5f));
  }
  else if (m_pos == 0 && nbButtons > 1) {
    MVMat = glm::translate(glm::mat4(1.f), glm::vec3(-0.2f, -0.14f, -0.5f));
  }
  else {
    MVMat = glm::translate(glm::mat4(1.f), glm::vec3(0.2f, -0.14f, -0.5f));
  }

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

  if(nbButtons == 0) {
    glBindTexture(GL_TEXTURE_2D, this->texS);
  }

  if (cursor == 0) {
    glBindTexture(GL_TEXTURE_2D, this->texS);
  } else {
    glBindTexture(GL_TEXTURE_2D, this->tex);
  }

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindTexture(GL_TEXTURE_2D, 0);
  glActiveTexture(GL_TEXTURE0);

  glBindVertexArray(0);
}

void Button::swapTexture () {
  if( cursor == 1) {
    cursor = 0;
  } else {
    cursor = 1;
  }
}
