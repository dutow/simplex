
#pragma once

#include <glm/vec3.hpp>

#include "simplex/drawable/uniform_object.hpp"

namespace simplex {

  namespace world3d {

    class uniform_sun : public uniform_object {
    public:
      uniform_sun(uint64_t cycle_time_in_microsec);

      void update(uint64_t elapsed_microsec);

      virtual void modify(shader& target) override;

    private:
      uint64_t cycle_time_in_microsec;
      uint64_t current_cycle_pos;

      glm::vec3 sun_direction;
      glm::vec3 sun_color;
      float sun_indensity;
    };

  }
}