
#include "shader.hpp"

#include <vector>
#include "easylogging++.h"

#include "simplex/drawable/shader_source.hpp"
#include "simplex/error/shader_error.hpp"

namespace simplex {

shader::shader(std::unique_ptr<shader_source> _source) : source(std::move(_source)) {
    loaded = false;

    GLuint vertex_shader_id = compile_shader(GL_VERTEX_SHADER, source->name(), source->vertex_shader());
    GLuint fragment_shader_id = compile_shader(GL_FRAGMENT_SHADER, source->name(), source->fragment_shader());

    program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);

    GLint result = GL_FALSE;
    int log_length;
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);
    std::vector<char> link_log((log_length > 1) ? log_length : 1);
    glGetProgramInfoLog(program_id, log_length, NULL, &link_log[0]);
    std::string log_str(link_log.begin(), link_log.end());
    if (result == GL_TRUE) {
        if (log_length > 0) {

            LOG(INFO) << "Shader linking log: " << log_str;
        }
    } else {  // GL_FALSE
        auto exc = new shader_error(source->name(), 0, "linking", log_str);
        LOG(FATAL) << *exc;
        throw exc;
    }

	glDetachShader(program_id, vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

    loaded = true;
}

GLuint shader::compile_shader(GLuint shader_type, std::string shader_name, std::string shader_source) {
    GLuint shader_id = glCreateShader(shader_type);

    GLint result = GL_FALSE;
    int log_length;

    const char* shader_cstr = shader_source.c_str();
    glShaderSource(shader_id, 1, &shader_cstr, NULL);
    glCompileShader(shader_id);

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

    std::vector<char> shader_log((log_length > 1) ? log_length : 1);
    glGetShaderInfoLog(shader_id, log_length, NULL, &shader_log[0]);
    std::string log_str(shader_log.begin(), shader_log.end());
    if (result == GL_TRUE) {
        if (log_length > 0) {

            LOG(INFO) << "Shader compilation log: " << log_str;
        }
    } else {  // GL_FALSE
        auto exc = new shader_error(shader_name, shader_type, "compiling", log_str);
        LOG(FATAL) << *exc;
        throw exc;
    }

    return shader_id;
}

shader::~shader() { unload(); }

void shader::unload() {
    glDeleteProgram(program_id);
    loaded = false;
}

void shader::activate() {
    glUseProgram(program_id);
    GLuint result = glGetError();

	if (result != GL_NO_ERROR) {
		// TODO! automatic reload?
		LOG(ERROR) << "Lost shader: " << source->name();
	}
}

bool shader::is_loaded() {
    loaded = glIsProgram(program_id) == GL_TRUE;

    return loaded;
}
}