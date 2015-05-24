
#include "raymarch.hpp"

#include <easylogging++.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

namespace simplex {
  namespace raycast {

    raymarch::raymarch(obj_type type, world3d::camera& cam, world3d::uniform_sun& sun) : camera(cam), sun(sun), type(type)
    {

    }

    void raymarch::load_assets(asset_loaders loaders)
    {
      if (!loaders.shaders.has("raymarch")) {
        loaders.shaders.add("raymarch");
      }
      rm_shader = &loaders.shaders["raymarch"];

      if (!loaders.drawables.has("2d_quad11")) {
        LOG(FATAL) << "2d_quad11 required!";
      }
      quad = &loaders.drawables["2d_quad11"];
    }

    void raymarch::render()
    {
      // TODO: parameter!
      glm::mat4 rm_world = glm::translate<float>(glm::vec3(-2.0f, 1.0f, 0.0f));

      rm_shader->activate();

      rm_shader->uniform_mat4x4("viewProj", camera.get_mvp_matrix());
      rm_shader->uniform_mat4x4("viewIprojI", glm::inverse(camera.get_mvp_matrix()));
      //rm_shader->uniform_mat4x4("view", camera.get_view_matrix());
      rm_shader->uniform_mat4x4("model", rm_world);
      rm_shader->uniform_mat4x4("modelI", glm::inverse(rm_world));
      //rm_shader->uniform_int("DO_REFINE", 5);
      //rm_shader->uniform_int("object_type", static_cast<int>(type));

      sun.modify(*rm_shader);

      quad->render();
    }

  }
}