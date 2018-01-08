#include "draw.hpp"

using namespace glimac;

static GLuint texFromFile(std::string path) {
  auto img = loadImage(path);
  GLuint tex = 0;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexImage2D(
               GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0, 
               GL_RGBA, GL_FLOAT, img->getPixels()
               );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  return tex;
}


Vertex2DUV::Vertex2DUV(float x, float y, float u, float v)
    : position(x,y), texcoords(u,v)
    {}


GLuint SphereDraw::texPacman(0);
size_t SphereDraw::refcount(0);

SphereDraw::SphereDraw(Sphere * sphere){

  if(!refcount){
    texPacman = texFromFile("assets/textures/murSimple.png");
  }

  ++refcount;

  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

  glBufferData(GL_ARRAY_BUFFER, sphere->getVertexCount()*sizeof(ShapeVertex), sphere->getDataPointer(), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

  const GLuint VERTEX_ATTR_POSITION = 0;
  glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
  glVertexAttribPointer(
                        VERTEX_ATTR_POSITION,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(ShapeVertex),
                        (const GLvoid*)offsetof(ShapeVertex, position)
                        );

  const GLuint VERTEX_ATTR_NORMAL = 1;
  glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
  glVertexAttribPointer(
                        VERTEX_ATTR_NORMAL,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(ShapeVertex),
                        (const GLvoid*)offsetof(ShapeVertex, normal)
                        );

  const GLuint VERTEX_ATTR_TEXCOORDS = 2;
  glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
  glVertexAttribPointer(
                        VERTEX_ATTR_TEXCOORDS,
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(ShapeVertex),
                        (const GLvoid*)offsetof(ShapeVertex, texCoords)
                        );

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // Les matrices
  this->ProjMatrix = glm::perspective( glm::radians(70.f), 800.f / 600.f, 0.1f, 100.f);
  this->NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

  glEnable(GL_DEPTH_TEST);

}
void SphereDraw::drawSphere(Sphere *sphere, GLuint locationMVPMatrix, GLuint locationMVMatrix, GLuint locationNormalMatrix){
  glBindVertexArray(this->vao);

  glUniformMatrix4fv(locationMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));

  glUniformMatrix4fv(locationMVMatrix, 1, GL_FALSE, glm::value_ptr(this->MVMatrix));

  glUniformMatrix4fv(locationNormalMatrix, 1, GL_FALSE, glm::value_ptr(this->NormalMatrix));

  glDrawArrays(GL_TRIANGLES, 0, sphere->getVertexCount());
  glBindVertexArray(0);

}

void SphereDraw::drawPacman(Sphere *sphere, GLuint locationMVPMatrix, GLuint locationMVMatrix, GLuint locationNormalMatrix, glm::mat4 MVMat, GLint uTexture){
  glBindVertexArray(this->vao);

  MVMatrix = MVMat;

  glUniformMatrix4fv(locationMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
  glUniformMatrix4fv(locationMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
  glUniformMatrix4fv(locationNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

  static const size_t TEXUNIT = 0;
  glUniform1i(uTexture, TEXUNIT);
  glActiveTexture(GL_TEXTURE0 + TEXUNIT);
  glBindTexture(GL_TEXTURE_2D, this->texPacman);

  glDrawArrays(GL_TRIANGLES, 0, sphere->getVertexCount());

  glBindTexture(GL_TEXTURE_2D, 0);
  glActiveTexture(GL_TEXTURE0);

  glBindVertexArray(0);

}

SphereDraw::~SphereDraw(){
  glDeleteBuffers(1, &this->vbo);
  glDeleteVertexArrays(1, &this->vao);
}

GLuint WallDraw::tex(0);
GLuint WallDraw::texP(0);
size_t WallDraw::refcount(0);

WallDraw::WallDraw(){

  if(!refcount){
    tex = texFromFile("assets/textures/murSimple.png");
    texP = texFromFile("assets/textures/sol.png");
  }

  ++refcount;

  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

  static const Vertex2DUV vdata[] = {
    Vertex2DUV(-0.5f, -0.5f,  1, 1),
    Vertex2DUV( 0.5f, -0.5f,  0, 1),
    Vertex2DUV( -0.5f, 0.5f, 1, 0),
    Vertex2DUV( 0.5f, 0.5f, 0, 0)
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

  ProjMatrix = glm::perspective (glm::radians(70.f),(float)800/600,0.1f,100.f);
  NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

}

WallDraw::~WallDraw() {
  //--refcount;
  if(!refcount)
    glDeleteTextures(1, &tex);

  glDeleteBuffers(1, &this->vbo);
  glDeleteVertexArrays(1, &this->vao);
}

glm::mat3 translate(float tx, float ty) {
	glm::mat3 M = glm::mat3(glm::vec3(1,0,0), glm::vec3(0,1,0), glm::vec3(tx,ty,1));
	return M;
}

glm::mat3 scale(float tx, float ty) {
	glm::mat3 M = glm::mat3(glm::vec3(tx,0,0), glm::vec3(0,ty,0), glm::vec3(0,0,1));
	return M;
}

glm::mat3 rotate(float a) {
	glm::mat3 M = glm::mat3(glm::vec3(cos(a),-sin(a),0), glm::vec3(sin(a),cos(a),0), glm::vec3(0,0,1));
	return M;
}

void WallDraw::drawWall(GLuint locationMVPMatrix, GLuint locationMVMatrix, GLuint locationNormalMatrix, glm::mat4 MVMat, GLint uTexture){

  glBindVertexArray(this->vao);

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

void WallDraw::drawPathWall(GLuint locationMVPMatrix, GLuint locationMVMatrix, GLuint locationNormalMatrix, glm::mat4 MVMat, GLint uTexture){

  glBindVertexArray(this->vao);

  MVMatrix = MVMat;

  glUniformMatrix4fv(locationMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
  glUniformMatrix4fv(locationMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
  glUniformMatrix4fv(locationNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

  static const size_t TEXUNIT = 0;
  glUniform1i(uTexture, TEXUNIT);
  glActiveTexture(GL_TEXTURE0 + TEXUNIT);
  glBindTexture(GL_TEXTURE_2D, this->texP);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindTexture(GL_TEXTURE_2D, 0);
  glActiveTexture(GL_TEXTURE0);

  glBindVertexArray(0);
}

PathDraw::PathDraw(){
}

PathDraw::~PathDraw(){
}

void PathDraw::drawPathThirdPerson(GLuint locationMVPMatrix, GLuint locationMVMatrix, GLuint locationNormalMatrix, Level level, Player player, GLint uTexture){
  glm::mat4 MVMat = glm::mat4(1.f);
  static WallDraw pathWall;

  pathWall.ProjMatrix = glm::translate(pathWall.ProjMatrix, glm::vec3(0,12,0));
  pathWall.ProjMatrix = glm::rotate(pathWall.ProjMatrix, -0.5f, glm::vec3(1,0,0));

  for (int i=0 ; i<(int)level.map.size() ; i++){
    if (level.map[i].type != 0){
      // dessin chemin
      int translateX = level.map[i].position.x - (int)level.width/2;
      int translateY = level.map[i].position.y - (int)level.height/2;

      MVMat = glm::translate (glm::mat4(1.f), glm::vec3(translateX,-translateY,-18));
      pathWall.drawPathWall(locationMVPMatrix,locationMVMatrix,locationNormalMatrix,MVMat,uTexture);

      // dessin murs
      if (level.map[i-1].type == 0){
        glm::mat4 MVMatWallL = glm::translate(MVMat, glm::vec3(-0.5f, 0, 0.5f));
        MVMatWallL = glm::rotate(MVMatWallL, 1.5708f, glm::vec3(0, 0, 1));
        MVMatWallL = glm::rotate(MVMatWallL, 1.5708f, glm::vec3(1, 0, 0));
        pathWall.drawWall(locationMVPMatrix,locationMVMatrix,locationNormalMatrix,MVMatWallL,uTexture);
      }
      if (level.map[i+1].type == 0){
        glm::mat4 MVMatWallR = glm::translate(MVMat, glm::vec3(0.5f, 0, 0.5f));
        MVMatWallR = glm::rotate(MVMatWallR, 1.5708f, glm::vec3(0, 0, 1));
        MVMatWallR = glm::rotate(MVMatWallR, 1.5708f, glm::vec3(1, 0, 0));    
        pathWall.drawWall(locationMVPMatrix,locationMVMatrix,locationNormalMatrix,MVMatWallR,uTexture);
      }
      if (level.map[i-level.width].type == 0){
        glm::mat4 MVMatWallU = glm::translate(MVMat, glm::vec3(0, 0.5f, 0.5f));
        MVMatWallU = glm::rotate(MVMatWallU, 1.5708f, glm::vec3(1, 0, 0));  
        pathWall.drawWall(locationMVPMatrix,locationMVMatrix,locationNormalMatrix,MVMatWallU,uTexture);
      }
      
      if (level.map[i+level.width].type == 0){
        glm::mat4 MVMatWallD = glm::translate(MVMat, glm::vec3(0, -0.5f, 0.5f));
        MVMatWallD = glm::rotate(MVMatWallD, 1.5708f, glm::vec3(1, 0, 0));   
        pathWall.drawWall(locationMVPMatrix,locationMVMatrix,locationNormalMatrix,MVMatWallD,uTexture);
      }

    }
  }

  // dessin Pacman
  Sphere sphere(0.5f, 16, 16);
  SphereDraw pacman (&sphere);
  pacman.ProjMatrix = pathWall.ProjMatrix;
  int translateX = player.position.x - (int)level.width/2;
  int translateY = player.position.y - (int)level.height/2;
  MVMat = glm::translate (glm::mat4(1.f), glm::vec3(translateX,-translateY,-17.5f));
  pacman.drawPacman(&sphere,locationMVPMatrix,locationMVMatrix,locationNormalMatrix, MVMat, uTexture);

  // dessin Fantomes
  std::vector<SphereDraw> ghosts;
  for (int i = 0 ; i < (int)level.ghosts.size() ; i++){
    Sphere sphere(0.5f, 16, 16);
    SphereDraw ghost (&sphere);
    ghosts.push_back(ghost);
    ghost.ProjMatrix = pathWall.ProjMatrix;
    int translateX = level.ghosts[i].position.x - (int)level.width/2;
    int translateY = level.ghosts[i].position.y - (int)level.height/2;
    MVMat = glm::translate (glm::mat4(1.f), glm::vec3(translateX,-translateY,-17.5f));
    ghost.drawPacman(&sphere,locationMVPMatrix,locationMVMatrix,locationNormalMatrix, MVMat, uTexture);
  }

  pathWall.ProjMatrix = glm::rotate(pathWall.ProjMatrix, 0.5f, glm::vec3(1,0,0));
  pathWall.ProjMatrix = glm::translate(pathWall.ProjMatrix, glm::vec3(0,-12,0));
  pacman.ProjMatrix = pathWall.ProjMatrix;
  for (int i = 0 ; i < (int)ghosts.size() ; i++){
    ghosts[i].ProjMatrix = pathWall.ProjMatrix;
  }

}

void PathDraw::drawPathFirstPerson(GLuint locationMVPMatrix, GLuint locationMVMatrix, GLuint locationNormalMatrix, Level level, Player player, GLint uTexture){
	glm::mat4 MVMat = glm::mat4(1.f);
  static WallDraw pathWall;

	for (int i=0 ; i<(int)level.map.size() ; i++){
		if (level.map[i].type != 0){
			int translateZ = player.position.x - level.map[i].position.x;
			int translateX = player.position.y - level.map[i].position.y;
			if (player.direction == 0){
				int temp = translateZ;
				translateZ = -translateX;
				translateX = temp;
			}
			else if (player.direction == 2){
				int temp = translateZ;
				translateZ = translateX;
				translateX = -temp;
			}
			else if (player.direction == 3){
				translateZ = -translateZ;
				translateX = -translateX;
			}

			MVMat = glm::translate (glm::mat4(1.f), glm::vec3(-translateX,-0.5f,translateZ));
			MVMat = glm::rotate(MVMat, 1.5708f, glm::vec3(1, 0, 0));
			pathWall.drawPathWall(locationMVPMatrix,locationMVMatrix,locationNormalMatrix,MVMat,uTexture);

			// dessin murs
			if (level.map[i-1].type == 0){
				// direction nord
				if (player.direction == 0) {
					MVMat = glm::translate (glm::mat4(1.f), glm::vec3(-translateX -0.5f,0.f,translateZ));
					MVMat = glm::rotate(MVMat, 1.5708f, glm::vec3(0, 1, 0));
				}
				// direction sud
				else if (player.direction == 2) {
					MVMat = glm::translate (glm::mat4(1.f), glm::vec3(-translateX +0.5f,0.f,translateZ));
					MVMat = glm::rotate(MVMat, 1.5708f, glm::vec3(0, 1, 0));
				}
				// direction est
				else if (player.direction == 1) MVMat = glm::translate (glm::mat4(1.f), glm::vec3(-translateX,0.f,translateZ + 0.5f));
				// direction ouest
				else if (player.direction == 3) MVMat = glm::translate (glm::mat4(1.f), glm::vec3(-translateX,0.f,translateZ - 0.5f));

				pathWall.drawWall(locationMVPMatrix,locationMVMatrix,locationNormalMatrix,MVMat,uTexture);
			}
			if (level.map[i+1].type == 0){
				// direction nord
				if (player.direction == 0) {
					MVMat = glm::translate (glm::mat4(1.f), glm::vec3(-translateX + 0.5f,0.f,translateZ));
					MVMat = glm::rotate(MVMat, 1.5708f, glm::vec3(0, 1, 0));
				}
				// direction sud
				else if (player.direction == 2) {
					MVMat = glm::translate (glm::mat4(1.f), glm::vec3(-translateX - 0.5f,0.f,translateZ));
					MVMat = glm::rotate(MVMat, 1.5708f, glm::vec3(0, 1, 0));
				}
				// direction est
				else if (player.direction == 1) MVMat = glm::translate (glm::mat4(1.f), glm::vec3(-translateX,0.f,translateZ - 0.5f));
				// direction ouest
				else if (player.direction == 3) MVMat = glm::translate (glm::mat4(1.f), glm::vec3(-translateX,0.f,translateZ + 0.5f));
				
				pathWall.drawWall(locationMVPMatrix,locationMVMatrix,locationNormalMatrix,MVMat,uTexture);
			}
			if (level.map[i-level.width].type == 0){
				// direction est
				if (player.direction == 1) {
					MVMat = glm::translate (glm::mat4(1.f), glm::vec3(-translateX - 0.5f,0.f,translateZ));
					MVMat = glm::rotate(MVMat, 1.5708f, glm::vec3(0, 1, 0));
				}
				// direction ouest
				else if (player.direction == 3) {
					MVMat = glm::translate (glm::mat4(1.f), glm::vec3(-translateX + 0.5f,0.f,translateZ));
					MVMat = glm::rotate(MVMat, 1.5708f, glm::vec3(0, 1, 0));
				}
				//direction nord
				else if (player.direction == 0) MVMat = glm::translate (glm::mat4(1.f), glm::vec3(-translateX,0.f,translateZ - 0.5f));
				//direction sud
				else if (player.direction == 2) MVMat = glm::translate (glm::mat4(1.f), glm::vec3(-translateX,0.f,translateZ + 0.5f));
				
				pathWall.drawWall(locationMVPMatrix,locationMVMatrix,locationNormalMatrix,MVMat,uTexture);
			}
			
			if (level.map[i+level.width].type == 0){
				// direction est
				if (player.direction == 1) {
					MVMat = glm::translate (glm::mat4(1.f), glm::vec3(-translateX + 0.5f,0.f,translateZ));
					MVMat = glm::rotate(MVMat, 1.5708f, glm::vec3(0, 1, 0));
				}
				// direction ouest
				else if (player.direction == 3) {
					MVMat = glm::translate (glm::mat4(1.f), glm::vec3(-translateX - 0.5f,0.f,translateZ));
					MVMat = glm::rotate(MVMat, 1.5708f, glm::vec3(0, 1, 0));
				}
				//direction nord
				else if (player.direction == 0) MVMat = glm::translate (glm::mat4(1.f), glm::vec3(-translateX,0.f,translateZ + 0.5f));
				//direction sud
				else if (player.direction == 2) MVMat = glm::translate (glm::mat4(1.f), glm::vec3(-translateX,0.f,translateZ - 0.5f));
				
				pathWall.drawWall(locationMVPMatrix,locationMVMatrix,locationNormalMatrix,MVMat,uTexture);
			}
		}
	}
}
