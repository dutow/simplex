
#pragma once

#include "simplex/drawable/shader_source.hpp"

namespace simplex {
/// <summary>	std::string based shader source. </summary>
class memory_shader_source : public shader_source {
   public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Creates a new shader source based on the given strings. </summary>
    ///
    /// <param name="program_name">		  	Name of the program. </param>
    /// <param name="vertex_shader_src">  	The vertex shader source. </param>
    /// <param name="fragment_shader_src">	The fragment shader source. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    memory_shader_source(std::string program_name, std::string vertex_shader_src, std::string fragment_shader_src)
        : program_name(program_name), vertex_shader_src(vertex_shader_src), fragment_shader_src(fragment_shader_src){};
    /// <summary>	Destructor. </summary>
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