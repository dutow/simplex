
#pragma once


#include "simplex/drawable/drawable.hpp"

#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <string>

namespace simplex {
  namespace primitive3d {

    /**
    * A quad with given coordinates.
    */
    class objfile : public drawable {
    public:

      objfile(std::string content);

      virtual void render() override;
    private:
      GLuint vbo_id;
      GLuint vao_id;  ///< Identifier for the vao

      uint16_t size;
    };
  }
} ///< .