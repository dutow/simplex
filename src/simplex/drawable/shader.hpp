
#pragma once

#include <memory>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <boost/core/noncopyable.hpp>


namespace simplex {

class shader_source;

/** A GLSL shader. */
class shader : private boost::noncopyable {
   public:
    /**
     * Creates and loads a new shader.
     *
     * @param _source Source for the shader programs.
     */
    shader(std::unique_ptr<shader_source> _source);
    ~shader();

    // void reload();
    // void ensure_loaded();

    /**
     * Query if this object is loaded in OpenGL.
     *
     * @return true if loaded, false if not.
     */
    bool is_loaded();

    /** Activates this shader. */
    void activate();

  /**
   * bind an integer.
   *
   * @param name  The name.
   * @param value The value.
   */
	void uniform_int(std::string name, int value);

  void uniform_float(std::string name, float value);

  /**
   * Binds a uniform 4x4 matrix.
   *
   * @param name   The name of the uniform parameter.
   * @param matrix The matrix.
   */
	void uniform_mat4x4(std::string name, glm::mat4x4 matrix);

  /**
   * Binds a vec2 vector.
   *
   * @param name     The name of the uniform parameter.
   * @param vertices The vertices.
   */
	void uniform_vec2fv(std::string name, std::vector<glm::vec2> vertices);

  /**
   * Binds a vec3 vector.
   *
   * @param name     The name of the uniform parameter.
   * @param vertices The vertices.
   */
	void uniform_vec3fv(std::string name, std::vector<glm::vec3> vertices);

  void uniform_vec3f(std::string name, glm::vec3 vec3);
  void uniform_vec4f(std::string name, glm::vec4 vec4);
  
  /**
   * Binds a vec4 vector.
   *
   * @param name     The name of the uniform parameter.
   * @param vertices The vertices.
   */
	void uniform_vec4fv(std::string name, std::vector<glm::vec4> vertices);

   private:
    std::unique_ptr<shader_source> source;  ///< Source for the

    GLuint program_id;
    bool loaded;

    /**
     * Compiles a shader.
     *
     * @param shader_type   Type of the shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER).
     * @param shader_name   Internal name of the shader.
     * @param shader_source The shader source code.
     *
     * @return A GLuint.
     */
    GLuint compile_shader(GLuint shader_type, std::string shader_name, std::string shader_source);

	GLint get_uniform_loc(std::string name) const;
	
    void unload();
};


}