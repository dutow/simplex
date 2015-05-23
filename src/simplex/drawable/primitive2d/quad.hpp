
#pragma once

#include "simplex/drawable/drawable.hpp"

#include <GL/glew.h>
#include <glm/vec2.hpp>

namespace simplex {
namespace primitive2d {

/**
 * A quad with given coordinates.
 */
class quad : public drawable {
   public:
    /**
     * Creates a quad with the given size.
     *
     * @param top_left     The top left coordinate.
     * @param bottom_right The bottom left coordinate.
     */
    quad(glm::vec2 top_left, glm::vec2 bottom_right);

    virtual void render() override;
private:
    GLuint vbo_id;  ///< Identifier for the vbo
    GLuint vao_id;  ///< Identifier for the vao
};
}
} ///< .