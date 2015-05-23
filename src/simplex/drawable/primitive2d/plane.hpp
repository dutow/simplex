
#pragma once

#include "simplex/drawable/drawable.hpp"

#include <GL/glew.h>
#include <glm/vec2.hpp>

namespace simplex {
  namespace primitive2d {

    class plane : public drawable {
    public:
      
      plane(glm::vec2 top_left, glm::vec2 bottom_right, glm::ivec2 steps);

      virtual void render() override;
    private:
      GLuint vertex_vbo_id;
      GLuint index_vbo_id;
      GLuint vao_id;  ///< Identifier for the vao

      uint16_t index_count;
    };
  }
} ///< .