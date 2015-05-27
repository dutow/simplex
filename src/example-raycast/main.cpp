
#include "example-raycast/config.hpp"
#include "simplex/simplex.hpp"

#include "easylogging++.h"

#include "GL/glew.h"
#include "GL/GL.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/rotate_vector.hpp>

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
    assets.drawables.add("suzanne", std::make_unique<simplex::primitive3d::objfile>(asset_loader->load_asset("suzanne.obj")));

    assets.shaders.add("standard");

    assets.textures.add("cubemap.jpg", simplex::texture::mode::CUBEMAP);

    assets.textures.add("heightmap.png");

    assets.textures.add("suzanne.png");

    assets.textures.add("world.jpg");

    skybox = std::make_unique<simplex::primitive3d::skybox>(assets.textures["cubemap.jpg"], cam);
    skybox->load_assets(assets);
        
    terrain = std::make_unique<simplex::primitive3d::heightmap>(assets.textures["heightmap.png"], cam, sun, glm::vec2(1024.0f, 1024.0f));
    terrain->load_assets(assets);
    terrain->move_camera_to_center();

    rc_raymarch = std::make_unique<simplex::raycast::raymarch>(simplex::raycast::obj_type::SPHERE, cam, sun);
    rc_raymarch->load_assets(assets);

    angle_diff = 0;

    campos = cam.get_camera_position();
    
    auto& camera_spot = sun.add_light(); // camera spotlight is always idx 1
    camera_spot.intensities = glm::vec3(1, 0, 0); //strong white light
    camera_spot.attenuation = 0.0001f;
    camera_spot.ambientCoefficient = 0.0f; //no ambient light
    camera_spot.coneAngle = 5.0f;

    glm::vec3 cp = cam.get_camera_position();
    camera_spot.position = glm::vec4(cp.x, cp.y - 0.4, cp.z, 1); // slightly below camera for more fun
    camera_spot.coneDirection = cam.get_camera_direction();
    
    // center point light
    auto& center_point = sun.add_light();
    center_point.intensities = glm::vec3(1.75, 0, 0); //strong white light
    center_point.attenuation = 0.0150f;
    center_point.ambientCoefficient = 0.0f; //no ambient light
    center_point.coneAngle = 360.0f;
    terrain->correct_camera_y();
    center_point.position = glm::vec4(campos.x, campos.y + 30.0, campos.z, 1);
    
    // add 5 more lights
    for (int i = 1; i <=5; i++) {
      glm::vec3 p = glm::rotateY(glm::vec3(7.0f * 3.5f, 10.0f, 0.0f), (2 * 3.14f / 5.0f * i));
      p.x += campos.x;
      p.z += campos.z;
      terrain->ensure_above_terrain(p, true);
      auto& cam_x = sun.add_light();
      cam_x.intensities = glm::vec3(0.3f * (i % 3), 0.3f * ((i+1)%3), 0.3f * ((i+2)%3)); //strong white light
      cam_x.attenuation = 0.050f;
      cam_x.ambientCoefficient = 0.0f; //no ambient light
      cam_x.coneAngle = 360.0f;
      cam_x.position = glm::vec4(p.x, p.y + 5.0, p.z, 1);
    }
  }

  virtual void render(uint64_t elapsed_microseconds) override {
    glDisable(GL_DEPTH_TEST);
    terrain->correct_camera_y();
    cam.update(elapsed_microseconds);
    sun.update(elapsed_microseconds);
    
    auto& camera_spot = sun[1]; // camera spotlight is always idx 1
    glm::vec3 cp = cam.get_camera_position();
    camera_spot.position = glm::vec4(cp.x, cp.y - 0.4, cp.z, 1);
    camera_spot.coneDirection = cam.get_camera_direction();
    
    skybox->render();

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    
    terrain->render();
        
    angle_diff += elapsed_microseconds;
    
    float diff = (angle_diff % 120000000) / 120000000.0f * 6.28f;
    rc_raymarch->set_center(campos);
    for (int i = 1; i <= 10; i++) {
      rc_raymarch->change_type(static_cast<simplex::raycast::obj_type>(i));
      for (int n = 1; n <= 3; n++) {
        
        glm::vec3 p = glm::rotateY(glm::vec3(7.0f * n, 10.0f, 0.0f), (2 * 3.14f / 10.0f * i) - diff);
        p.x += campos.x;
        p.z += campos.z;
        p.y = 15.0f;
        terrain->ensure_above_terrain(p, true);
        rc_raymarch->change_model_mat(glm::translate<float>(p));
        rc_raymarch->render();
      }
    }

    auto& std_shader = assets.shaders["standard"];
    std_shader.activate();
    std_shader.uniform_mat4x4("camera", cam.get_mvp_matrix());
    std_shader.uniform_mat4x4("view", cam.get_view_matrix());
    //std_shader.uniform_vec3f("light_position", campos);
    sun.modify(std_shader);

    assets.textures["suzanne.png"].bind(simplex::texture::unit::UNIT0);
    std_shader.uniform_int("tex_diffuse", 0);
    for (int i = 1; i <= 10; i++) {

      glm::vec3 p = glm::rotateY(glm::vec3(7.0f * 4, 10.0f, 0.0f), (2 * 3.14f / 10.0f * i) + diff);
      p.x += campos.x;
      p.z += campos.z;
      p.y = 15.0f;
      terrain->ensure_above_terrain(p, true);
      std_shader.uniform_mat4x4("model", glm::translate<float>(p));
      
      assets.drawables["suzanne"].render();
    }

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

  glm::vec3 campos;

  uint64_t angle_diff;
};

int main(int argc, char** argv) {
  raycast_application app(std::make_unique<simplex::program_arguments>(argc, argv));

  app.run();

  return 0;
}