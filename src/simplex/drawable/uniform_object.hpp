
#pragma once

#include <GL/glew.h>
#include <easylogging++.h>

#include "simplex/error/application_error.hpp"

namespace simplex {

class shader;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Simulated uniform object, to support ES2. The modify method is called when the object has to
/// update it's data.
/// </summary>
///
/// <remarks>	Might be linked to multiple shaders. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class uniform_object {
   public:
    /// <summary>	Default constructor. </summary>
    uniform_object(){};
    /// <summary>	Destructor. </summary>
    ~uniform_object(){};

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Modifies the shader's uniform parameters.. </summary>
    ///
    /// <param name="target">	[in,out] Target shader. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void modify(shader& target) = 0;
};
}