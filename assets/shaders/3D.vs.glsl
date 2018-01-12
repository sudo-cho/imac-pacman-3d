#version 330 core

// Attributs de sommet
layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;

// Matrices de transformations reçues en uniform
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

// Sorties du shader
out vec3 vPosition_vs;
out vec3 vNormal_vs;
out vec2 vTexCoords;
out vec4 vTotal;

void main() {
  // Passage en coordonnées homogènes
  vec4 vertexPosition = vec4(aVertexPosition, 1);
  vec4 vertexNormal = vec4(aVertexNormal, 0);

  // Calcul de la position projetée
  vPosition_vs = vec3(uMVMatrix * vertexPosition);
  vNormal_vs = vec3(uNormalMatrix * vertexNormal);
  vTexCoords = aVertexTexCoords;

  gl_Position = uMVPMatrix * vertexPosition;
  vTotal = gl_Position;
}
