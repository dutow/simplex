
#pragma once

#include "simplex/drawable/drawable.hpp"

#include <GL/glew.h>
#include <glm/vec2.hpp>

namespace simplex {
  namespace primitive3d {

    /**
    * A quad with given coordinates.
    */
    class sphere : public drawable {
    public:
      
      sphere(float radius, uint16_t rings, uint16_t sectors);

      virtual void render() override;
    private:
      GLuint vertex_vbo_id;
      GLuint normal_vbo_id;
      GLuint texcoord_vbo_id;
      GLuint index_vbo_id;
      GLuint vao_id;  ///< Identifier for the vao

      uint16_t index_count;
    };
  }
} ///< .