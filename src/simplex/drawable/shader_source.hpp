
#pragma once

#include <string>

namespace simplex {
/** A shader's source code &amp; internal name. */
class shader_source {
   public:
    /** Default constructor. */
    shader_source(){};
    /** Destructor. */
    virtual ~shader_source(){};

    /**
     * Gets the internal name.
     *
     * @return A std::string.
     */
    virtual std::string name() = 0;

    /**
     * Vertex shader source code.
     *
     * @return A std::string.
     */
    virtual std::string vertex_shader() = 0;

    /**
     * Fragment shader source code.
     *
     * @return A std::string.
     */
    virtual std::string fragment_shader() = 0;
};
}