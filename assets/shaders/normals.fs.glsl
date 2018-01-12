#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;
in vec4 vTotal;
uniform sampler2D uTexture;

uniform vec3 uKd;
uniform vec3 uKs;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;
uniform int uIsTransparent;

out vec4 fFragColor;

vec3 blinnPhong() {
  return (uLightIntensity/(distance( (vec3(vTotal.x+0.3,vTotal.y+0.5,vTotal.z-0)),uLightDir_vs)*distance((vec3(vTotal.x+0.3,vTotal.y+0.5,vTotal.z-0)),uLightDir_vs)) * (uKd*(dot( normalize(uLightDir_vs - vPosition_vs) , vNormal_vs )) + uKs*pow(dot( (normalize(uLightDir_vs - vPosition_vs)+normalize(-vPosition_vs))/2, vNormal_vs ),0.6)));
}

void main() {
  if(uIsTransparent == 0) {
    fFragColor = texture(uTexture, vTexCoords).rgba * vec4(blinnPhong(), 1);
  } else {
    fFragColor = texture(uTexture, vTexCoords).rgba;
  }
}
