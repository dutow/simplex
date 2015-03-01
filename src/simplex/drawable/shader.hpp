
#pragma once

#include <memory>
#include <string>
#include <vector>
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

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	bind an integer. </summary>
	///
	/// <param name="name"> 	The name. </param>
	/// <param name="value">	The value. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void uniform_int(std::string name, int value);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Binds a uniform 4x4 matrix. </summary>
	///
	/// <param name="name">  	The name of the uniform parameter. </param>
	/// <param name="matrix">	The matrix. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void uniform_mat4x4(std::string name, glm::mat4x4 matrix);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Binds a vec2 vector. </summary>
	///
	/// <param name="name">	   	The name of the uniform parameter. </param>
	/// <param name="vertices">	The vertices. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void uniform_vec2fv(std::string name, std::vector<glm::vec2> vertices);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Binds a vec3 vector. </summary>
	///
	/// <param name="name">	   	The name of the uniform parameter. </param>
	/// <param name="vertices">	The vertices. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void uniform_vec3fv(std::string name, std::vector<glm::vec3> vertices);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Binds a vec4 vector. </summary>
	///
	/// <param name="name">	   	The name of the uniform parameter. </param>
	/// <param name="vertices">	The vertices. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void uniform_vec4fv(std::string name, std::vector<glm::vec4> vertices);

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

	GLint get_uniform_loc(std::string name) const;
	
    void unload();
};


}