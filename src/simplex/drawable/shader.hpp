
#pragma once

#include <memory>
#include <string>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>

namespace simplex {

class shader_source;

/// <summary>	A GLSL shader. </summary>
class shader {
   public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Creates and loads a new shader. </summary>
    ///
    /// <param name="_source">	Source for the shader programs. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    shader(std::unique_ptr<shader_source> _source);
    ~shader();

    // void reload();
    // void ensure_loaded();

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Query if this object is loaded in OpenGL. </summary>
    ///
    /// <returns>	true if loaded, false if not. </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    bool is_loaded();

    /// <summary>	Activates this shader. </summary>
    void activate();

	// uniform functions
	void uniform_mat4x4(std::string name, glm::mat4x4 matrix);

   private:
    std::unique_ptr<shader_source> source;  ///< Source for the

    GLuint program_id;
    bool loaded;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Compiles a shader. </summary>
    ///
    /// <param name="shader_type">  	Type of the shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER). </param>
    /// <param name="shader_name">  	Internal name of the shader. </param>
    /// <param name="shader_source">	The shader source code. </param>
    ///
    /// <returns>	A GLuint. </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    GLuint compile_shader(GLuint shader_type, std::string shader_name, std::string shader_source);

    void unload();
};
}