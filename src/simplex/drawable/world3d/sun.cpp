
#include "sun.hpp"

#include <glm/gtx/rotate_vector.hpp>

#include "simplex/drawable/shader.hpp"

namespace simplex {

  namespace world3d {




    void uniform_sun::modify(shader& target)
    {
      target.uniform_vec3f("sun_direction", sun_direction);
      target.uniform_vec3f("sun_color", sun_color);
      target.uniform_float("sun_intensity", sun_indensity);
    }

    uniform_sun::uniform_sun(uint64_t cycle_time_in_microsec) : cycle_time_in_microsec(cycle_time_in_microsec)
    {
      sun_color = glm::vec3(192.0f / 256.0f, 191.0 / 256.0f, 173.0f / 256.0f);
      sun_indensity = 0.8f;
    }

    void uniform_sun::update(uint64_t elapsed_microsec)
    {
      current_cycle_pos += elapsed_microsec;
      if (current_cycle_pos > cycle_time_in_microsec) {
        current_cycle_pos %= cycle_time_in_microsec;
      }

      sun_direction = glm::rotateY(glm::vec3(1.0f, 1.0f, 0.0f), static_cast<float>(current_cycle_pos) / static_cast<float>(cycle_time_in_microsec) * 3.14f * 2.0f);
      
    }

  }
}