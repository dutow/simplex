
#pragma once

#include <string>
#include <memory>
#include <bitset>
#include <glm/mat4x4.hpp>

#include <boost/signals2.hpp>

#include "simplex/application/application.hpp"
#include "simplex/drawable/drawable_manager.hpp"
#include "simplex/drawable/shader_manager.hpp"
#include "simplex/application/clock.hpp"
#include "simplex/application/keycode.hpp"


namespace simplex {

class window;

/** Contains the current input (key, mouse) state. */
struct input_state {
  std::bitset<256> key_states;
  std::bitset<16>  mouse_buttons;
  glm::ivec2 mouse_coordinates;
};

/** Event signal runner for boost::signal. Runs signals until one returns true. */
struct event_signal {
  typedef bool result_type;

  template<typename InputIterator>
  result_type operator()(InputIterator first, InputIterator last) const
  {
    while (first != last) {
      if (*first)
        return true;
      ++first;
    }
    return false;
  }
};

/** Callbacks for easy delegated event handling */
struct event_handlers { // TODO: use a faster signal handler
  boost::signals2::signal<void(input_state const& input, window& wnd, uint64_t elapsed_inmicrosec)> on_render;

  boost::signals2::signal<bool(input_state const& input, window& wnd, char chr), event_signal> on_char;
  boost::signals2::signal<bool(input_state const& input, window& wnd, keycode kc), event_signal> on_keydown;
  boost::signals2::signal<bool(input_state const& input, window& wnd, keycode kc), event_signal> on_keyup;

  boost::signals2::signal<bool(input_state const& input, window& wnd, glm::ivec2 coord), event_signal> on_mousemove;
  boost::signals2::signal<bool(input_state const& input, window& wnd, glm::ivec2 coord, mouse_button btn), event_signal> on_mousedown;
  boost::signals2::signal<bool(input_state const& input, window& wnd, glm::ivec2 coord, mouse_button btn), event_signal> on_mouseup;
};

/** Implements a simple single window application. */
class single_window_application : public application {
   public:
     typedef application base_type;
    /**
     * Constructor.
     *
     * @param title                    The window's title.
     * @param width                    The window's width.
     * @param height                   The window's height.
     * @param program_args             The program arguments.
     * @param asset_loader_constructor The asset factory.
     */
    single_window_application(std::wstring title, unsigned int width, unsigned int height, std::unique_ptr<program_arguments> program_args,
                              asset_loader::constructor asset_loader_constructor = SIMPLEX_MAGIC_ASSET);

    /** Destructor. */
    virtual ~single_window_application();

    /** Runs the main loop of the application. */
    virtual void run();

   protected:
    /**
     * Renders the scene.
     *
     * @param elapsed_microseconds Elapsed microseconds since the previous call.
     */
    virtual void render(uint64_t elapsed_microseconds) = 0;

    glm::mat4 orthogonal_projection_screensize;  ///< Orthogonal projection matching the window size for 2D applications
    glm::mat4 orthogonal_projection_01;          ///< Orthogonal projection between 0..1

    // EVENT CALLBACKS

    virtual bool on_resize(window& wnd, glm::ivec2 new_size) override;

    virtual bool on_quit(window& wnd) override;

    virtual bool on_char(window& wnd, char chr) override;

    virtual bool on_keydown(window& wnd, keycode kc) override;

    virtual bool on_keyup(window& wnd, keycode kc) override;

    virtual bool on_mousemove(window& wnd, glm::ivec2 coord) override;

    virtual bool on_mousedown(window& wnd, glm::ivec2 coord, mouse_button btn) override;

    virtual bool on_mouseup(window& wnd, glm::ivec2 coord, mouse_button btn) override;

    void move_mouse_to(glm::ivec2 coord);

    input_state input;

    event_handlers event_handlers;

   private:
    std::unique_ptr<shader_manager> _shaders;      ///< Shader manager
    std::unique_ptr<drawable_manager> _drawables;  ///< Drawable manager

    std::unique_ptr<window> application_window;

    clock clk;

   protected:  // to fix initialization order
    // references to some members for nicer syntax
    // This is a class with few instances, memory footprint won't be a problem

    shader_manager& shaders;      ///< Shader manager
    drawable_manager& drawables;  ///< Drawable manager

    window& app_window;
    
};
}