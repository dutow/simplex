
#pragma once

#include <GL/glew.h>
#include <easylogging++.h>

#include "simplex/error/application_error.hpp"

namespace simplex {

class shader;

/**
 * Simulated uniform object, to support ES2. The modify method is called when the object has to
 * update it's data.
 *
 * ### remarks Might be linked to multiple shaders.
 */
class uniform_object {
   public:
    /** Default constructor. */
    uniform_object(){};
    /** Destructor. */
    virtual ~uniform_object(){};

    /**
     * Modifies the shader's uniform parameters.
     *
     * @param [in,out] target Target shader.
     */
    virtual void modify(shader& target) = 0;
};
}