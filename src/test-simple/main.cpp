
#include "simplex/simplex.hpp"

#include "easylogging++.h"

#include "GL/glew.h"
#include "GL/GL.h"

INITIALIZE_EASYLOGGINGPP

class test_application : public simplex::single_window_application {
   public:
    test_application() : single_window_application(L"Hello OpenGL", 400, 400), q(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)) {

        std::string vertex_shader(R"xx(#version 330 core
layout(location = 0) in vec2 vertexPosition_modelspace;
void main(){
  gl_Position.xy = vertexPosition_modelspace;
  gl_Position.z = 1.0;
  gl_Position.w = 1.0;
}
)xx");

        std::string fragment_shader(R"xx(#version 330 core
out vec3 color;
void main()
{
    color = vec3(1,0,0);
}
)xx");

        shader = (std::make_unique<simplex::shader>(std::make_unique<simplex::memory_shader_source>("test_shader", vertex_shader, fragment_shader)));
    }

    virtual void render() override {
        // nop
        shader->activate();
        q.render();
    }

   private:
    simplex::primitive2d::quad q;
    std::unique_ptr<simplex::shader> shader;
};

int main() {
    test_application app;

    app.run();

    return 0;
}