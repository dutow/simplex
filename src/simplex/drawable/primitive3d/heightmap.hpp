
#pragma once

#include "simplex/drawable/drawable.hpp"

#include <GL/glew.h>
#include <glm/vec4.hpp>

namespace simplex {
  namespace primitive3d {

    /**
    * A quad with given coordinates.
    *
    * @author Zsolt Parragi
    * @date 2015-05-23
    */
    class heightmap : public drawable {
    public:
      /**
      * Creates a heightmap.
      */
      heightmap();


      virtual void render();
    private:
      GLuint vbo_id;  ///< Identifier for the vbo
      GLuint vao_id;  ///< Identifier for the vao
    };
  }
} ///< .