
#pragma once

#include <memory>
#include <string>
#include <GL/glew.h>

namespace simplex {

class shader_source;

class shader {
   public:
    shader(std::unique_ptr<shader_source> _source);
    ~shader();

    // void reload();
    // void ensure_loaded();

    bool is_loaded();

    void activate();

   private:
    std::unique_ptr<shader_source> source;

    GLuint program_id;  ///< Identifier for the program
    bool loaded;

    GLuint compile_shader(GLuint shader_type, std::string shader_name, std::string shader_source);

    void unload();
};
}