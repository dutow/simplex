
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
      terrain_shader->uniform_mat4x4("view", camera.get_view_matrix());
      terrain_shader->uniform_vec3f("cameraPosition", camera.get_camera_position());

      sun.modify(*terrain_shader);
      terrain_plane->render();
    }

    void heightmap::load_assets(asset_loaders loaders)
    {
      terrain_plane = std::make_unique<simplex::primitive2d::plane>(glm::vec2(0.0f, 0.0f), size, glm::ivec2(128, 128));
      
      // read the texture data
      terrain_heightmap.bind(simplex::texture::unit::UNIT0);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
      heights.resize(width*height * 4);

      glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &heights[0]);

      if (!loaders.shaders.has("heightmap")) {
        loaders.shaders.add("heightmap");
      }
      terrain_shader = &loaders.shaders["heightmap"];
    }

    void heightmap::move_camera_to_center()
    {
      world3d::free_camera* fc = dynamic_cast<world3d::free_camera*>(&camera);

      if (fc) {
        glm::vec3 half(size.x / 2, 15.0f, size.y / 2);
        fc->move_to(half);
      }
    }

    heightmap::~heightmap()
    {

    }

    void heightmap::ensure_above_terrain(glm::vec3 &point, bool force)
    {
      int x = static_cast<int>(ceil(point.x / size.x * width));
      int y = static_cast<int>(ceil(point.z / size.y * height));
      float xd = (point.x / size.x * width) - x;
      float yd = (point.z / size.y * height) - y;
      int xf = static_cast<int>(floor(point.x / size.x * width));
      int yf = static_cast<int>(floor(point.z / size.y * height));
      if (x < 0 || y < 0 || xf >= width || yf >= height) {
        LOG(WARNING) << "BAD " << point.x << "->" << x << " " << point.z << "->" << y << " " << width << " " << height;
        x = width / 2;
        y = height / 2;
        point.x = x / static_cast<float>(width)* size.x;
        point.y = y / static_cast<float>(height)* size.y;
      }

      float t_at = (0
        + value_at(x, y) * (2 - xd - yd)
        + value_at(xf, yf) * (xd + yd)
        ) / 2.0f
        ;

      if (force || point.y < t_at) {
        if (force) t_at += 3.0f;
        point.y = t_at;
      }

    }

    void heightmap::correct_camera_y()
    {
      world3d::free_camera* fc = dynamic_cast<world3d::free_camera*>(&camera);

      if (fc) {
        glm::vec3 pos = fc->get_camera_position();
        
        ensure_above_terrain(pos, false);

        fc->move_to(pos);
      }
    }

    float heightmap::value_at(int x, int y) const
    {
      return heights[y * width + x * 4] / 255.0f * 10.0f + 5.0f;
    }

  }
}