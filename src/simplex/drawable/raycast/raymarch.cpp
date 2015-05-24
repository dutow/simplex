
#include "raymarch.hpp"

#include <easylogging++.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

namespace simplex {
  namespace raycast {

    raymarch::raymarch(obj_type type, world3d::camera& cam, world3d::uniform_sun& sun) : camera(cam), sun(sun), type(type)
    {
      model_mat  = glm::translate<float>(glm::vec3(0.0f, 0.0f, 0.0f));
    }

    void raymarch::load_assets(asset_loaders loaders)
    {
      if (!loaders.shaders.has("raymarch")) {
        loaders.shaders.add("raymarch");
      }
      rm_shader = &loaders.shaders["raymarch"];

      if (!loaders.drawables.has("cube1")) {
        LOG(FATAL) << "cube1 required!";
      }
      quad = &loaders.drawables["cube1"];
    }

    void raymarch::render()
    {
      rm_shader->activate();

      rm_shader->uniform_mat4x4("viewProj", camera.get_mvp_matrix());
      rm_shader->uniform_mat4x4("viewIprojI", glm::inverse(camera.get_mvp_matrix()));
      //rm_shader->uniform_mat4x4("view", camera.get_view_matrix());
      rm_shader->uniform_mat4x4("model", model_mat);
      rm_shader->uniform_mat4x4("modelI", glm::inverse(model_mat));
      //rm_shader->uniform_int("DO_REFINE", 5);
      rm_shader->uniform_int("object_type", static_cast<int>(type));
      rm_shader->uniform_vec3f("screen_size", glm::vec3(800,800,0));

      rm_shader->uniform_vec3f("cameraPosition", camera.get_camera_position());

      // lights!

      sun.modify(*rm_shader);

      quad->render();
    }

    void raymarch::change_type(obj_type new_type)
    {
      type = new_type;
    }

    void raymarch::change_model_mat(glm::mat4 model)
    {
      model_mat = model;
    }

  }
}