
#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include <boost/core/noncopyable.hpp>

  
#pragma once

namespace simplex {
  namespace world3d {
    class camera : private boost::noncopyable {
    public:
      camera();
      virtual ~camera();

      virtual void reset();

      void set_viewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
      void set_clipping(double near_distance, double far_distance);
      void set_field_of_view(double fov);

      /** Calculates the new matrices based on the changed properties. */
      virtual void update(uint64_t elapsed_microseconds);

      glm::mat4 const& get_mvp_matrix() const;

      glm::vec3 const& get_camera_look_at() const;
      glm::vec3 const& get_camera_direction() const;
      glm::vec3 const& get_camera_up() const;
      glm::vec3 const& get_camera_position() const;

      glm::ivec2 get_viewport_center() const;

    protected: // used  by subclasses
      glm::vec3 camera_position;
      glm::vec3 camera_look_at;

      glm::quat rotation_quaternion;

    private:

      uint32_t viewport_x;
      uint32_t viewport_y;
      uint32_t viewport_width;
      uint32_t viewport_height;

      double aspect;
      double field_of_view;
      double near_clip;
      double far_clip;

      glm::vec3 camera_direction;
      glm::vec3 camera_up;

      glm::mat4 projection;
      glm::mat4 view;
      glm::mat4 model;
      glm::mat4 mvp;
    };
  }
}