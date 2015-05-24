
#include "camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "easylogging++.h"


namespace simplex {
  namespace world3d {


    camera::camera()
    {
      camera_up = glm::vec3(0.0, 1.0, 0.0);
      field_of_view = 45;
      rotation_quaternion = glm::quat(1, 0, 0, 0);
      camera_position = glm::vec3(0.0, -3.0, -5.0);
      camera_look_at = glm::vec3(0.0, 0.0, -1.0);
    }

    camera::~camera()
    {

    }

    void camera::reset()
    {

    }

    void camera::set_viewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
    {
      viewport_x = x;
      viewport_y = y;
      viewport_width = w;
      viewport_height = h;

      aspect = static_cast<double>(w) / static_cast<double>(h);
    }

    void camera::set_clipping(double near_distance, double far_distance)
    {
      near_clip = near_distance;
      far_clip = far_distance;
    }

    void camera::set_field_of_view(double fov)
    {
      field_of_view = fov;
    }

    glm::mat4 const& camera::get_mvp_matrix() const
    {
      return mvp;
    }

    void camera::update(uint64_t elapsed_microseconds)
    {
      camera_direction = glm::normalize(camera_look_at - camera_position);

      projection = glm::perspective(field_of_view, aspect, near_clip, far_clip);
      
      glm::quat temp = glm::normalize(rotation_quaternion);

      camera_direction = glm::rotate(temp, camera_direction);
      camera_look_at = camera_position + camera_direction * 1.0f;
      
      view = glm::lookAt(camera_position, camera_look_at, camera_up);
      model = glm::mat4(1.0f);
      mvp = projection * view * model;
    }

    glm::vec3 const& camera::get_camera_look_at() const
    {
      return camera_look_at;  
    }

    glm::vec3 const& camera::get_camera_direction() const
    {
      return camera_direction;
    }

    glm::vec3 const& camera::get_camera_up() const
    {
      return camera_up;
    }

    glm::vec3 const& camera::get_camera_position() const
    {
      return camera_position;
    }

    glm::ivec2 camera::get_viewport_center() const
    {
      return glm::ivec2(viewport_x + viewport_width / 2, viewport_y + viewport_height / 2);
    }

    glm::mat4 const& camera::get_view_matrix() const
    {
      return view;
    }

  }
}