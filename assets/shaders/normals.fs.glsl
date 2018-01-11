#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
uniform sampler2D uTexture;
in vec2 vTexCoords;
out vec4 fFragColor;

void main() {
  // fFragColor = normalize(vNormal_vs);
  fFragColor = texture(uTexture, vTexCoords).rgba;
}
