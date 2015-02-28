
#pragma once

#include "simplex/drawable/drawable.hpp"

#include <GL/glew.h>
#include <glm/vec2.hpp>

namespace simplex {
namespace primitive2d {

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A quad with given coordinates. </summary>
///
/// <remarks>	The implementation doesn't check the coordinates! </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class quad : public drawable {
   public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Creates a quad with the given size. </summary>
    ///
    /// <param name="top_left">	   	The top left coordinate. </param>
    /// <param name="bottom_right">	The bottom left coordinate. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    quad(glm::vec2 top_left, glm::vec2 bottom_right);

    virtual void render();
private:
    GLuint vbo_id;
	GLuint vao_id;
};
}
}