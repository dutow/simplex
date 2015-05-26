
#pragma once

#include <GL/glew.h>
#include <glm/vec4.hpp>


#include "simplex/drawable/drawable.hpp"
#include "simplex/drawable/asset_aware.hpp"
#include "simplex/drawable/shader.hpp"
#include "simplex/drawable/texture.hpp"
#include "simplex/drawable/world3d/camera.hpp"
#include "simplex/drawable/world3d/sun.hpp"

namespace simplex {
  namespace primitive3d {

    class heightmap : public drawable, public asset_aware {
    public:
      /**
      * Creates a heightmap.
      */
      heightmap(texture& terrain_heightmap, world3d::camera& camera, world3d::uniform_sun& sun, glm::vec2 size);
      ~heightmap();

      virtual void load_assets(asset_loaders loaders) override;

      virtual void render() override;

      // camera interaction stuff
      void move_camera_to_center();

      void correct_camera_y();

      void ensure_above_terrain(glm::vec3 &point, bool force=true);

    private:
      world3d::camera& camera;
      world3d::uniform_sun& sun;

      texture& terrain_heightmap;

      glm::vec2 size;

      std::unique_ptr<drawable> terrain_plane;

      shader* terrain_shader;

      std::vector<float> heights;
      GLint width, height;

      float value_at(int x, int y) const;

      void postprocess_texture(texture& tex, std::vector<float>& heights, int& width, int& height);
    };
  }
} ///< .