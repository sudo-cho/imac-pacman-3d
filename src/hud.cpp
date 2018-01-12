#include <hud.hpp>

struct Vertex2DUV{
  glm::vec2 position, texcoords;
  Vertex2DUV(float x, float y, float u, float v);
};

Heart::Heart (const int pos, GLuint tex)
  : pos(pos), tex(tex)
{
  this->initHeart();
}
Heart::~Heart () {}

Hud::Hud () {}
Hud::~Hud () {}

void Hud::initHearts () {
  Heart heart1(0, texFromFile("assets/textures/heart.png"));
  Heart heart2(1, texFromFile("assets/textures/heart.png"));
  Heart heart3(2, texFromFile("assets/textures/heart.png"));

  hearts.push_back(heart1);
  hearts.push_back(heart2);
  hearts.push_back(heart3);
}

void Hud::removeHeart () {
    hearts.pop_back();
}

void Heart::initHeart () {
  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

  static const Vertex2DUV vdata[] = {
    Vertex2DUV(-0.05f, -0.05f,  1, 1),
    Vertex2DUV( 0.05f, -0.05f,  0, 1),
    Vertex2DUV( -0.05f, 0.05f, 1, 0),
    Vertex2DUV( 0.05f, 0.05f, 0, 0)
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

  ProjMatrix = glm::perspective(glm::radians(90.f), 1.8f, 0.1f, 100.f);
  NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
}

void Heart::drawHeart(GLuint locationMVPMatrix, GLuint locationMVMatrix, GLuint locationNormalMatrix, GLint uTexture) {
  glBindVertexArray(this->vao);

  glm::mat4 MVMat;
  if (pos == 0) {
    MVMat = glm::translate(glm::mat4(1.f), glm::vec3(-0.8f, 0.42f, -0.5f));
  }
  else if (pos == 1) {
    MVMat = glm::translate(glm::mat4(1.f), glm::vec3(-0.7f, 0.42f, -0.5f));
  }
  else {
    MVMat = glm::translate(glm::mat4(1.f), glm::vec3(-0.6f, 0.42f, -0.5f));
  }

  MVMat = glm::rotate(MVMat, 3.14159f, glm::vec3(0.f, 1.f, 0.f));
  MVMatrix = MVMat;

  glUniformMatrix4fv(locationMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
  glUniformMatrix4fv(locationMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
  glUniformMatrix4fv(locationNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

  static const size_t TEXUNIT = 0;
  glUniform1i(uTexture, TEXUNIT);
  glActiveTexture(GL_TEXTURE0 + TEXUNIT);
  glBindTexture(GL_TEXTURE_2D, this->tex);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindTexture(GL_TEXTURE_2D, 0);
  glActiveTexture(GL_TEXTURE0);

  glBindVertexArray(0);

}
