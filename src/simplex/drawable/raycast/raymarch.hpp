
#pragma once

#include "simplex/drawable/drawable.hpp"
#include "simplex/drawable/asset_aware.hpp"
#include "simplex/drawable/shader.hpp"
#include "simplex/drawable/asset_aware.hpp"
#include "simplex/drawable/world3d/camera.hpp"
#include "simplex/drawable/world3d/sun.hpp"

#include <GL/glew.h>

namespace simplex {
  namespace raycast {

    enum class obj_type { SPHERE = 1 };

    class raymarch : public drawable, public asset_aware {
    public:
      
      raymarch(obj_type type, world3d::camera& cam, world3d::uniform_sun& sun);

      virtual void load_assets(asset_loaders loaders) override;

      virtual void render() override;
    private:
      shader* rm_shader;
      world3d::camera& camera;
      world3d::uniform_sun& sun;
      obj_type type;
      drawable* quad;
    };
  }
} ///< .