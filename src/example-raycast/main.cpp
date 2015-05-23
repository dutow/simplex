
#include "example-raycast/config.hpp"
#include "simplex/simplex.hpp"

#include "easylogging++.h"

#include "GL/glew.h"
#include "GL/GL.h"

INITIALIZE_EASYLOGGINGPP

/**
* A test application.
*
* @author Zsolt Parragi <zsolt.parragi@cancellar.hu>
* @date 2015-05-23
*/
class raycast_application : public simplex::single_window_application {
public:
  typedef simplex::single_window_application base_type;

  raycast_application(std::unique_ptr<simplex::program_arguments> program_args)
    : single_window_application(L"Newton Fractal", 400, 400, std::move(program_args)) {

    cam.set_clipping(0.01f, 10000.0f);

    drawables.add_drawable("heightmap", std::make_unique<simplex::primitive3d::heightmap>());

    shaders.add_shader("heightmap");

    cam.register_input_handlers(event_handlers, app_window);
  }

  virtual void render(uint64_t elapsed_microseconds) override {
    auto& shader = shaders["heightmap"];
    shader.activate();

    cam.update(elapsed_microseconds);

    shader.uniform_mat4x4("camera", cam.get_mvp_matrix());
    drawables["heightmap"].render();
  }

  virtual bool on_resize(simplex::window& wnd, glm::ivec2 new_size) override {
    //poly.resize_canvas(new_size);
    cam.set_viewport(0, 0, new_size.x, new_size.y);
    return base_type::on_resize(wnd, new_size);
  }

private:
  simplex::world3d::free_camera cam;
};

int main(int argc, char** argv) {
  raycast_application app(std::make_unique<simplex::program_arguments>(argc, argv));

  app.run();

  return 0;
}