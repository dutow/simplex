
#include "example-newton-fractal/config.hpp"
#include "simplex/simplex.hpp"

#include "easylogging++.h"

#include "GL/glew.h"
#include "GL/GL.h"

#include "polynom.hpp"

INITIALIZE_EASYLOGGINGPP

/**
 * A test application.
 *
 * @author Zsolt Parragi <zsolt.parragi@cancellar.hu>
 * @date 2015-05-23
 */
class newton_fractal_application : public simplex::single_window_application {
   public:
    newton_fractal_application(std::unique_ptr<simplex::program_arguments> program_args)
    : single_window_application(L"Newton Fractal", 400, 400, std::move(program_args)), poly(glm::ivec2(400,400)) {

        assets.shaders.add("fractal");
  
    }

    virtual void render(uint64_t elapsed_microseconds) override {
      auto& shader = assets.shaders["fractal"];
        shader.activate();
    poly.update(elapsed_microseconds);
    poly.modify(shader);
        shader.uniform_mat4x4("projection", orthogonal_projection_01);
    
        assets.drawables["2d_quad01"].render();
    }
  virtual bool on_resize(simplex::window& wnd, glm::ivec2 new_size) {
    poly.resize_canvas(new_size);

    return single_window_application::on_resize(wnd, new_size);
  }

  virtual bool on_char(simplex::window& wnd, char chr) {
    if (chr == 'r') {
      poly.randomize();
      return true;
    }
    if (chr == '+') {
      // add root
      poly.add_random_root();
      return true;
    }

    return false;
  }
private:
    polynom poly;
};

int main(int argc , char** argv) {
    newton_fractal_application app(std::make_unique<simplex::program_arguments>(argc, argv));

    app.run();

    return 0;
}