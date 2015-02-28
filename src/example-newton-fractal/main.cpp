////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	G:\cppdev\simplex\src\test-simple\main.cpp
//
// summary:	Implements the main class
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "test-simple/config.hpp"
#include "simplex/simplex.hpp"

#include "easylogging++.h"

#include "GL/glew.h"
#include "GL/GL.h"

INITIALIZE_EASYLOGGINGPP

/// <summary>	A test application. </summary>
class newton_fractal_application : public simplex::single_window_application {
   public:
	   newton_fractal_application(std::unique_ptr<simplex::program_arguments> program_args) : single_window_application(L"Newton Fractal", 400, 400, std::move(program_args)), q(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)) {

       shader = (std::make_unique<simplex::shader>(std::make_unique<simplex::asset_shader_source>(*assets, "fractal")));
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

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Main entry-point for this application. </summary>
///
/// <param name="argc">	Number of command-line arguments. </param>
/// <param name="argv">	Array of command-line argument strings. </param>
///
/// <returns>	Exit-code for the process - 0 for success, else an error code. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {
    newton_fractal_application app(std::make_unique<simplex::program_arguments>(argc, argv));

    app.run();

    return 0;
}