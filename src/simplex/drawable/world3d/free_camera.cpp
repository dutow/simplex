
#include "free_camera.hpp"

#include <easylogging++.h>

namespace simplex {
namespace world3d {


  const float ROTATION_FACTOR = 10.0f;
  const float MOVEMENT_FACTOR = 25.0f;

glm::vec3 free_camera::forward_one() const { return get_camera_direction(); }

glm::vec3 free_camera::rightward_one() const { return glm::cross(get_camera_direction(), get_camera_up()); }

void free_camera::update(uint64_t elapsed_microseconds) {
    calc_full_speed();
    glm::vec3 move_vector = speed_vector * (static_cast<float>(elapsed_microseconds) / 1000000.0f);
    camera_position += move_vector;
    camera_look_at += move_vector;

    base_type::update(elapsed_microseconds);
}

void free_camera::stop() {
    // TODO: delayed stop with slowing down?
    speed_vector = glm::vec3();
}

glm::vec3 free_camera::get_speed_vector() const { return speed_vector; }

void free_camera::set_forward_vector(free_camera::speed sp) { forward = sp; }

void free_camera::set_rightward_vector(free_camera::speed sp) { rightward = sp; }

void free_camera::calc_full_speed() {
    stop();
    speed_vector += forward_one() * static_cast<float>(forward) * MOVEMENT_FACTOR;
    speed_vector += rightward_one() * static_cast<float>(rightward)* MOVEMENT_FACTOR;
}

free_camera::free_camera() : forward(free_camera::speed::ZERO), rightward(free_camera::speed::ZERO) {}

void free_camera::register_input_handlers(simplex::event_handlers& handlers, simplex::window& wnd) {
    handlers.on_keydown.connect([&](input_state const&, window&, keycode kc) {
        switch (kc) {
            case simplex::keycode::UP: {
                set_forward_vector(simplex::world3d::free_camera::speed::PLUS);
                return true;
            }
            case simplex::keycode::DOWN: {
                set_forward_vector(simplex::world3d::free_camera::speed::MINUS);
                return true;
            }
            case simplex::keycode::LEFT: {
                set_rightward_vector(simplex::world3d::free_camera::speed::MINUS);
                return true;
            }
            case simplex::keycode::RIGHT: {
                set_rightward_vector(simplex::world3d::free_camera::speed::PLUS);
                return true;
            }
        }
        return false;
    });

    handlers.on_keyup.connect([&](input_state const&, window&, keycode kc) {
        switch (kc) {
            case simplex::keycode::UP:
            case simplex::keycode::DOWN: {
                set_forward_vector(simplex::world3d::free_camera::speed::ZERO);
                return true;
            }
            case simplex::keycode::LEFT:
            case simplex::keycode::RIGHT: {
                set_rightward_vector(simplex::world3d::free_camera::speed::ZERO);
                return true;
            }
        }
        return false;
    });

    handlers.on_mousemove.connect([&](input_state const& input, window& wnd, glm::ivec2 coord) {
      
      if (input.mouse_buttons[static_cast<int>(mouse_button::MIDDLE)]) {
        if (get_viewport_center() == coord) return true;

        glm::ivec2 diff = get_viewport_center() - coord;
        mouse_control.coord -= diff;
        mouse_control.coord_changed = true;
        wnd.move_cursor_to(get_viewport_center());
      }
      return false;
    });

    handlers.on_render.connect([&](input_state const& input, window& wnd, uint64_t elapsed_inmicrosec) {
      
      if (mouse_control.coord_changed) {
        
        camera_heading = - static_cast<float>(mouse_control.coord.x) / 180.0f * 3.14f * (static_cast<float>(elapsed_inmicrosec) / 1000000.0f) * ROTATION_FACTOR;
        camera_pitch = static_cast<float>(mouse_control.coord.y) / 180.0f * 3.14f * (static_cast<float>(elapsed_inmicrosec) / 1000000.0f) * ROTATION_FACTOR;

        glm::vec3 axis = glm::cross(get_camera_direction(), get_camera_up());
        glm::quat pitch_quat = glm::angleAxis(camera_pitch, axis);
        glm::quat heading_quat = glm::angleAxis(camera_heading, get_camera_up());

        rotation_quaternion = glm::cross(pitch_quat, heading_quat);
      }
      else {
        rotation_quaternion = glm::quat(1, 0, 0, 0);
      }
      mouse_control.coord = glm::ivec2();
      mouse_control.coord_changed = false;
    });
}

void free_camera::move_to(glm::vec3 position)
{
  glm::vec3 direction = camera_look_at - camera_position;
  camera_position = position;
  camera_look_at = camera_position + direction;
}

}
}