
#pragma once

#include "simplex/drawable/shader_source.hpp"

namespace simplex {
/** std::string based shader source. */
class memory_shader_source : public shader_source {
   public:
    /**
     * Creates a new shader source based on the given strings.
     *
     * @param program_name        Name of the program.
     * @param vertex_shader_src   The vertex shader source.
     * @param fragment_shader_src The fragment shader source.
     */
    memory_shader_source(std::string program_name, std::string vertex_shader_src, std::string fragment_shader_src)
        : program_name(program_name), vertex_shader_src(vertex_shader_src), fragment_shader_src(fragment_shader_src){};
    /** Destructor. */
    virtual ~memory_shader_source(){};

    virtual std::string name() { return program_name; }

    virtual std::string vertex_shader() { return vertex_shader_src; }
    virtual std::string fragment_shader() { return fragment_shader_src; }

   private:
    std::string program_name;
    std::string vertex_shader_src;
    std::string fragment_shader_src;
};
}