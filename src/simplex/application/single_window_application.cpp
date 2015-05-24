
#include "single_window_application.hpp"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "simplex/window/window.hpp"

#include "simplex/drawable/primitive2d/quad.hpp"
#include "simplex/drawable/primitive3d/cube.hpp"

namespace simplex {

single_window_application::single_window_application(std::wstring title, unsigned int width, unsigned int height,
                                                     std::unique_ptr<program_arguments> program_args, asset_loader::constructor asset_loader_constructor)
    : application(std::move(program_args), asset_loader_constructor),
      orthogonal_projection_screensize(glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height))),
      orthogonal_projection_01(glm::ortho(0.0f, 1.0f, 0.0f, 1.0f)),
      _shaders(std::make_unique<shader_manager>(*asset_loader)),
      _drawables(std::make_unique<drawable_manager>()),
      _textures(std::make_unique<texture_manager>(*asset_loader)),
      application_window(window::create(*this, title, width, height)),
      clk(),
      assets(*_shaders, *_drawables, *_textures),
      app_window(*application_window.get()) {
    // add the 0..1 quad to the drawables, it's always useful
    assets.drawables.add("2d_quad01", std::make_unique<primitive2d::quad>(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)));
    assets.drawables.add("2d_quad11", std::make_unique<primitive2d::quad>(glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f)));
    assets.drawables.add("cube1", std::make_unique<primitive3d::cube>(0.2f));
}

void single_window_application::run() {
    application_window->show();
    clk = clock(); // reset clock at the beginning
  uint64_t elapsed = 0;
    while (application_window->is_running()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

        event_handlers.on_render(input, app_window, elapsed);
        render(elapsed);
        application_window->swap_buffers();
    elapsed = clk.elapsed_microseconds();
    }
}

single_window_application::~single_window_application() {}

bool single_window_application::on_resize(window& wnd, glm::ivec2 new_size) {
    glViewport(0, 0, new_size.x, new_size.y);
    orthogonal_projection_screensize = glm::ortho(0.0f, static_cast<float>(new_size.x), 0.0f, static_cast<float>(new_size.y));
    return true;
}

bool single_window_application::on_quit(window& wnd)
{
  return true;
}

bool single_window_application::on_char(window& wnd, char chr)
{
  return event_handlers.on_char(input, wnd, chr);
}

bool single_window_application::on_keydown(window& wnd, keycode kc)
{
  input.key_states[static_cast<int>(kc)] = true;
  return event_handlers.on_keydown(input, wnd, kc);
}

bool single_window_application::on_keyup(window& wnd, keycode kc)
{
  input.key_states[static_cast<int>(kc)] = false;
  return event_handlers.on_keyup(input, wnd, kc);
}

void single_window_application::move_mouse_to(glm::ivec2 coord)
{
  base_type::move_mouse_to(*application_window.get(), coord);
}

bool single_window_application::on_mousemove(window& wnd, glm::ivec2 coord)
{
  input.mouse_coordinates = coord;
  return event_handlers.on_mousemove(input, wnd, coord);
}

bool single_window_application::on_mousedown(window& wnd, glm::ivec2 coord, mouse_button btn)
{
  input.mouse_buttons[static_cast<int>(btn)] = true;
  return event_handlers.on_mousedown(input, wnd, coord, btn);
}

bool single_window_application::on_mouseup(window& wnd, glm::ivec2 coord, mouse_button btn)
{
  input.mouse_buttons[static_cast<int>(btn)] = false;
  return event_handlers.on_mouseup(input, wnd, coord, btn);
}

}