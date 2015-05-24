
#include "heightmap.hpp"

#include "easylogging++.h"

#include <vector>
#include <GL/glew.h>
#include <glm/vec3.hpp>

#include "simplex/drawable/primitive2d/plane.hpp"
#include "simplex/drawable/world3d/free_camera.hpp"

namespace simplex {
  namespace primitive3d {
    heightmap::heightmap(texture& terrain_heightmap, world3d::camera& camera, world3d::uniform_sun& sun, glm::vec2 size) : camera(camera), sun(sun), terrain_heightmap(terrain_heightmap), size(size) {

    }

    void heightmap::render() {
      terrain_heightmap.bind(simplex::texture::unit::UNIT0);

      terrain_shader->activate();
      terrain_shader->uniform_int("terrain", 0);
      terrain_shader->uniform_mat4x4("camera", camera.get_mvp_matrix());

      sun.modify(*terrain_shader);

      terrain_plane->render();
    }

    void heightmap::load_assets(asset_loaders loaders)
    {
      terrain_plane = std::make_unique<simplex::primitive2d::plane>(glm::vec2(0.0f, 0.0f), size, glm::ivec2(128, 128));

      if (!loaders.shaders.has("heightmap")) {
        loaders.shaders.add("heightmap");
      }
      terrain_shader = &loaders.shaders["heightmap"];
    }

    void heightmap::move_camera_to_center()
    {
      world3d::free_camera* fc = dynamic_cast<world3d::free_camera*>(&camera);

      if (fc) {
        glm::vec3 half(size.x / 2, 3.0f, size.y / 2);
        fc->move_to(half);
      }
    }

    heightmap::~heightmap()
    {

    }

  }
}