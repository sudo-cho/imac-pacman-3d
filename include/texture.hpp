#include <glimac/Image.hpp>

struct TextureObject{
  GLint texture=0;
}

// std::string earth_map_path = applicationPath.dirPath()
//   + "../../GLImac-Template/assets/textures/EarthMap.jpg";

// std::unique_ptr<Image> earth_map_img = loadImage(earth_map_path);
// if(!earth_map_img) {
//   std::cerr << "N'a pas pu charger " << earth_map_path << " !" << std::endl;
//   return EXIT_FAILURE;
// }

// glGenTextures(1, &this->texture);

// glBindTexture(GL_TEXTURE_2D, this->texture);
// glTexImage2D(
//              GL_TEXTURE_2D, 0, GL_RGBA,
//              earth_map_img->getWidth(), earth_map_img->getHeight(), 0,
//              GL_RGBA, GL_FLOAT, earth_map_img->getPixels()
//              );
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// glBindTexture(GL_TEXTURE_2D, 0);

// // pour activer la texture
// glActiveTexture(GL_TEXTURE0 + EARTH_TEXUNIT);
// glBindTexture(GL_TEXTURE_2D, this->texture);

// // delete après la texture
// glDeleteTextures(1, &earth_map_tex);
