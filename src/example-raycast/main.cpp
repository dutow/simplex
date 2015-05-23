
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
    : single_window_application(L"Newton Fractal", 800, 800, std::move(program_args)) {

    cam.set_clipping(0.01f, 10000.0f);
    cam.register_input_handlers(event_handlers, app_window);

    assets.drawables.add("plane128", std::make_unique<simplex::primitive2d::plane>( glm::vec2(0.0f,0.0f), glm::vec2(100.0f,100.0f), glm::ivec2(128,128) ));

    assets.shaders.add("heightmap");

    assets.textures.add("cubemap.jpg", simplex::texture::mode::CUBEMAP);

    assets.textures.add("heightmap.png");

    skybox = std::make_unique<simplex::primitive3d::skybox>(assets.textures["cubemap.jpg"], cam);
    skybox->load_assets(assets);
        
    terrain = std::make_unique<simplex::primitive3d::heightmap>(assets.textures["heightmap.png"], cam, glm::vec2(124.0f, 124.0f));
    terrain->load_assets(assets);
    terrain->move_camera_to_center();

    }

  virtual void render(uint64_t elapsed_microseconds) override {
    glDisable(GL_DEPTH_TEST);
    cam.update(elapsed_microseconds);

    skybox->render();

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    terrain->render();
  }

  virtual bool on_resize(simplex::window& wnd, glm::ivec2 new_size) override {
    //poly.resize_canvas(new_size);
    cam.set_viewport(0, 0, new_size.x, new_size.y);
    return base_type::on_resize(wnd, new_size);
  }

private:
  simplex::world3d::free_camera cam;
  std::unique_ptr<simplex::primitive3d::skybox> skybox;
  std::unique_ptr<simplex::primitive3d::heightmap> terrain;
};

int main(int argc, char** argv) {
  raycast_application app(std::make_unique<simplex::program_arguments>(argc, argv));

  app.run();

  return 0;
}