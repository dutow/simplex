
#include "sun.hpp"

#include <sstream>
#include <glm/gtx/rotate_vector.hpp>

#include "simplex/drawable/shader.hpp"

namespace simplex {

  namespace world3d {


    std::string p_name(size_t idx, std::string prop) {
      std::ostringstream ss;
      ss << "allLights[" << idx << "]." << prop;
      return ss.str();
    }

    void uniform_sun::modify(shader& target)
    {
      target.uniform_int("numLights", static_cast<int>(lights.size()));
      for (size_t i = 0; i < lights.size(); ++i) {
        target.uniform_vec4f(p_name(i, "position"), lights[i].position);
        target.uniform_vec3f(p_name(i, "intensities"), lights[i].intensities);
        target.uniform_float(p_name(i, "attenuation"), lights[i].attenuation);
        target.uniform_float(p_name(i, "ambientCoefficient"), lights[i].ambientCoefficient);
        target.uniform_float(p_name(i, "coneAngle"), lights[i].coneAngle);
        target.uniform_vec3f(p_name(i, "coneDirection"), lights[i].coneDirection);
      }
    }

    uniform_sun::uniform_sun(uint64_t cycle_time_in_microsec) : cycle_time_in_microsec(cycle_time_in_microsec)
    {
      sun_color = glm::vec3(0.4, 0.3, 0.1);
      sun_indensity = 0.8f;
    }



    void uniform_sun::update(uint64_t elapsed_microsec)
    {
      current_cycle_pos += elapsed_microsec;
      if (current_cycle_pos > cycle_time_in_microsec) {
        current_cycle_pos %= cycle_time_in_microsec;
      }

      sun_direction = glm::rotateY(glm::vec3(1.0f, -1.0f, 0.0f), static_cast<float>(current_cycle_pos) / static_cast<float>(cycle_time_in_microsec) * 3.14f * 2.0f);

      if (lights.size() == 0) {
        lights.resize(1);
      }

      lights[0].position.x = sun_direction.x;
      lights[0].position.y = sun_direction.y;
      lights[0].position.z = sun_direction.z;
      lights[0].position.w = 0;
      lights[0].intensities = sun_color;
      lights[0].ambientCoefficient = 0.7f;
    }

    light& uniform_sun::add_light(light l /*= light()*/)
    {
      lights.push_back(l);
      return lights[lights.size() - 1];
    }

    light& uniform_sun::operator[](size_t id)
    {
      return lights[id];
    }

  }
}