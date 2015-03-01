////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	G:\cppdev\simplex\src\test-simple\main.cpp
//
// summary:	Implements the main class
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "example-newton-fractal/config.hpp"
#include "simplex/simplex.hpp"

#include "easylogging++.h"

#include "GL/glew.h"
#include "GL/GL.h"

#include "polynom.hpp"

INITIALIZE_EASYLOGGINGPP


/// <summary>	A test application. </summary>
class newton_fractal_application : public simplex::single_window_application {
   public:
    newton_fractal_application(std::unique_ptr<simplex::program_arguments> program_args)
        : single_window_application(L"Newton Fractal", 400, 400, std::move(program_args)), poly({ glm::vec2(100.0f, 100.0f), glm::vec2(200.0f, 200.0f) }) {

        shaders.add_shader("fractal");
	
    }

    virtual void render() override {
        auto& shader = shaders["fractal"];
        shader.activate();
		poly.modify(shader);
        shader.uniform_mat4x4("projection", orthogonal_projection_01);

        drawables["quad01"].render();
    }

private:
    polynom poly;
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