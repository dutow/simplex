
#pragma once

#include "simplex/drawable/world3d/camera.hpp"
#include "simplex/drawable/texture.hpp"
#include "simplex/drawable/shader.hpp"
#include "simplex/drawable/drawable.hpp"
#include "simplex/drawable/asset_aware.hpp"

namespace simplex {
  namespace primitive3d {

    // TODO: implement library assets for shaders
    class skybox : public drawable, public asset_aware {
    public:

      skybox(texture& sky_texture, world3d::camera& camera);
      virtual ~skybox();

      virtual void render() override;

      virtual void load_assets(asset_loaders loaders) override;

      virtual asset_loader::path shader_path() const;

    private:

      texture& sky_texture;
      world3d::camera& camera;

      shader* sky_shader;

      drawable* sky_quad;

    };

  }
}