
#include "example-raycast/config.hpp"
#include "simplex/simplex.hpp"

#include "easylogging++.h"

#include "GL/glew.h"
#include "GL/GL.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

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
    : single_window_application(L"Newton Fractal", 800, 800, std::move(program_args)), sun(20*1000000) {

    cam.set_clipping(0.01f, 10000.0f);
    cam.register_input_handlers(event_handlers, app_window);

    assets.drawables.add("sphere1", std::make_unique<simplex::primitive3d::sphere>( 30.0f, 32, 32 ));
    assets.drawables.add("cube1", std::make_unique<simplex::primitive3d::cube>(20.0f));
    assets.drawables.add("suzanne", std::make_unique<simplex::primitive3d::objfile>(asset_loader->load_asset("suzanne.obj")));

    assets.shaders.add("standard");

    assets.textures.add("cubemap.jpg", simplex::texture::mode::CUBEMAP);

    assets.textures.add("heightmap.png");

    assets.textures.add("suzanne.png");

    assets.textures.add("world.jpg");

    skybox = std::make_unique<simplex::primitive3d::skybox>(assets.textures["cubemap.jpg"], cam);
    skybox->load_assets(assets);
        
    terrain = std::make_unique<simplex::primitive3d::heightmap>(assets.textures["heightmap.png"], cam, sun, glm::vec2(124.0f, 124.0f));
    terrain->load_assets(assets);
    terrain->move_camera_to_center();

    rc_raymarch = std::make_unique<simplex::raycast::raymarch>(simplex::raycast::obj_type::SPHERE, cam, sun);
    rc_raymarch->load_assets(assets);

    }

  virtual void render(uint64_t elapsed_microseconds) override {
    glDisable(GL_DEPTH_TEST);
    terrain->correct_camera_y();
    cam.update(elapsed_microseconds);
    sun.update(elapsed_microseconds);

    skybox->render();

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    
    terrain->render();


    // draw a suzanne
    

    auto& std_shader = assets.shaders["standard"];
    std_shader.activate();
    std_shader.uniform_mat4x4("camera", cam.get_mvp_matrix());
    sun.modify(std_shader);

    assets.textures["suzanne.png"].bind(simplex::texture::unit::UNIT0);
    std_shader.uniform_int("tex_diffuse", 0);

    assets.drawables["suzanne"].render();

    glm::vec3 pos;

    rc_raymarch->change_type(simplex::raycast::obj_type::SPHERE);
    pos = glm::vec3(10.0f, 1.0f, 10.0f);
    terrain->ensure_above_terrain(pos);
    rc_raymarch->change_model_mat(glm::translate<float>(pos));
    rc_raymarch->render();

    rc_raymarch->change_type(simplex::raycast::obj_type::TORUS);
    pos = glm::vec3(16.0f, 1.0f, 10.0f);
    terrain->ensure_above_terrain(pos);
    rc_raymarch->change_model_mat(glm::translate<float>(pos));
    rc_raymarch->render();
  }

  virtual bool on_resize(simplex::window& wnd, glm::ivec2 new_size) override {
    //poly.resize_canvas(new_size);
    cam.set_viewport(0, 0, new_size.x, new_size.y);
    return base_type::on_resize(wnd, new_size);
  }

private:
  simplex::world3d::free_camera cam;
  simplex::world3d::uniform_sun sun;

  std::unique_ptr<simplex::primitive3d::skybox> skybox;
  std::unique_ptr<simplex::primitive3d::heightmap> terrain;

  std::unique_ptr<simplex::raycast::raymarch> rc_raymarch;
};

int main(int argc, char** argv) {
  raycast_application app(std::make_unique<simplex::program_arguments>(argc, argv));

  app.run();

  return 0;
}