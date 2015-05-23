
#include "skybox.hpp"

namespace simplex {
  namespace world3d {

  };

  primitive3d::skybox::skybox(texture& sky_texture, world3d::camera& camera) : sky_texture(sky_texture), camera(camera)
  {

  }

  primitive3d::skybox::~skybox()
  {

  }

  void primitive3d::skybox::render()
  {
    sky_texture.bind(texture::unit::UNIT0);
    sky_shader->activate();
    sky_shader->uniform_mat4x4("projection", camera.get_mvp_matrix());
    sky_shader->uniform_int("texUnit", 0);
    sky_quad->render();
  }

  void primitive3d::skybox::load_assets(asset_loaders loaders)
  {
    if (!loaders.shaders.has(shader_path())) {
      loaders.shaders.add(shader_path());
    }
    sky_shader = &loaders.shaders[shader_path()];

    if (!loaders.drawables.has("2d_quad11")) {
      LOG(FATAL) << "Requires 2d_quad11 drawable";
    }
    sky_quad = &loaders.drawables["2d_quad11"];
  }

  asset_loader::path primitive3d::skybox::shader_path() const
  {
    return asset_loader::path("skybox");
  }

}