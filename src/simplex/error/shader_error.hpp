
#pragma once

#include <string>
#include <GL/glew.h>

#include "simplex/error/simplex_error.hpp"

namespace simplex {
/// <summary>	An error with a GLSL shader. </summary>
class shader_error : public simplex_error {
   public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Constructor. </summary>
    ///
    /// <param name="shader_name">  	Shader name for identifying the source. </param>
    /// <param name="shader_type">  	Type of the shader (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, or 0). </param>
    /// <param name="error_msg">		Message describing the error. </param>
    /// <param name="error_details">	Details of the error. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    shader_error(const std::string shader_name, const GLuint shader_type, const std::string error_msg, const std::string error_details) : simplex_error(error_msg), shader_name(shader_name), shader_type(shader_type), error_details(error_details) {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Writes the exception message to the log </summary>
    ///
    /// <param name="os">	[in,out] Log output stream. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void log(el::base::type::ostream_t& os) const {
		std::string shader_type_str(shader_type == GL_VERTEX_SHADER ? "VERTEX" : (shader_type == GL_FRAGMENT_SHADER ? "FRAGMENT" : "PROGRAM"));
        if (error_details.length() > 0) {
            os << "Shader error with shader " << shader_name << "[" << shader_type_str << "] while " << error_msg << ":" << error_details;
        } else {
			os << "Shader error with shader " << shader_name << "[" << shader_type_str << "]: " << error_msg;
        }
    }

   private:
    const std::string shader_name;
    const GLuint shader_type;
    const std::string error_details;
};
}