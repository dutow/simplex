
#include "texture.hpp"

#include <SOIL/SOIL.h>

namespace simplex {


  texture::texture(asset_loader const& assets, asset_loader::path texture_path, texture::mode texture_mode) : texture_mode(texture_mode)
  {
    auto asset = assets.load_binary_asset(texture_path);
    switch (texture_mode) {
    case mode::T_2D: {
      texture_id = SOIL_load_OGL_texture_from_memory(static_cast<unsigned char*>(&asset[0]), static_cast<int>(asset.size()), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
      break;
    }
    case mode::CUBEMAP: {
      texture_id = SOIL_load_OGL_single_cubemap_from_memory(static_cast<unsigned char*>(&asset[0]), static_cast<int>(asset.size()), "WNESUD", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
      break;
    }
    }
  }

  texture::~texture()
  {
    if (texture_id != 0) {
      glDeleteTextures(1, &texture_id);
    }
  }

  void texture::bind(unit u)
  {
    glActiveTexture(static_cast<int>(u));
    glBindTexture(texture_mode == mode::T_2D ? GL_TEXTURE_2D : GL_TEXTURE_CUBE_MAP, texture_id);
  }

}