
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

    enum class obj_type { SPHERE = 1, TORUS = 2, CUBE = 3, TORUS82 = 4, HUNT1 = 5, HUNT2 = 6, TRIRISM = 7, TORUS8 = 8, SPHERE4 = 9 };

    class raymarch : public drawable, public asset_aware {
    public:
      
      raymarch(obj_type type, world3d::camera& cam, world3d::uniform_sun& sun);

      virtual void load_assets(asset_loaders loaders) override;

      virtual void render() override;

      // todo: think about how to store object state
      void change_model_mat(glm::mat4 model);
      void change_type(obj_type new_type);
    private:
      shader* rm_shader;
      world3d::camera& camera;
      world3d::uniform_sun& sun;
      obj_type type;
      drawable* quad;
      glm::mat4 model_mat;
    };
  }
} ///< .