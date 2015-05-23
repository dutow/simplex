
#pragma once

#include "simplex/window/window.hpp"
#include "simplex/application/single_window_application.hpp"
#include "simplex/drawable/world3d/camera.hpp"

namespace simplex {
  namespace world3d{

    class free_camera : public camera {
    public:
      // TODO: parameters!

      typedef camera base_type;

      enum class speed { MINUS = -1, ZERO = 0, PLUS = 1 };

      free_camera();

      void move_to(glm::vec3 position);

      virtual void update(uint64_t elapsed_microseconds) override;

      void set_forward_vector(speed sp);
      void set_rightward_vector(speed sp);
      
      /** Stops the camera movement. */
      void stop();

      glm::vec3 forward_one() const;
      glm::vec3 rightward_one() const;

      glm::vec3 get_speed_vector() const;

      void register_input_handlers(event_handlers& handlers, window& wnd);

    protected:

      float camera_heading;
      float camera_pitch;

      speed forward;
      speed rightward;

      /** Calculates the full speed from the forward/rightward components. */
      void calc_full_speed();

      glm::vec3 speed_vector;

      struct {
        glm::ivec2 coord;
        bool coord_changed;
      } mouse_control;
    };
  }
}