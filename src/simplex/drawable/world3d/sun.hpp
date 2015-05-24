
#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "simplex/drawable/uniform_object.hpp"

namespace simplex {

  namespace world3d {

    struct light {
      glm::vec4 position;
      glm::vec3 intensities; //a.k.a. the color of the light
      float attenuation;
      float ambientCoefficient;
      float coneAngle; // new
      glm::vec3 coneDirection; // new
    };

    // TODO: rename to light
    class uniform_sun : public uniform_object {
    public:
      uniform_sun(uint64_t cycle_time_in_microsec);

      void update(uint64_t elapsed_microsec);

      virtual void modify(shader& target) override;

      light& add_light(light l = light());

      light& operator[](size_t id);

    private:
      uint64_t cycle_time_in_microsec;
      uint64_t current_cycle_pos;

      glm::vec3 sun_direction;
      glm::vec3 sun_color;
      float sun_indensity;

      std::vector<light> lights;
    };

  }
}