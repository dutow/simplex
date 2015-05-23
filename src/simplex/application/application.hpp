
#pragma once

#include <memory>
#include <glm/vec2.hpp>

#include "simplex/assets/magic_asset_loader.hpp"
#include "simplex/application/program_arguments.hpp"
#include "simplex/application/keycode.hpp"
#include "simplex/window/window.hpp"

namespace simplex {


/** Minimal class representing an application. */
class application {
   public:
    /**
     * Initializes the application.
     *
     * @param program_args             The program arguments.
     * @param asset_loader_constructor The asset factory.
     */
    application(std::unique_ptr<program_arguments> program_args, asset_loader::constructor asset_loader_constructor)
        : program_args(std::move(program_args)), assets(std::move(asset_loader_constructor(get_program_args()))){};

    /** Destructor. */
    virtual ~application(){};

    /** Runs the main loop of the application. */
    virtual void run() = 0;

    /**
     * Returns the program arguments.
     *
     * @return The program arguments.
     */
    program_arguments const& get_program_args() const { return *program_args; }

    /**
     * Called when the window is resizd.
     *
     * @param [in,out] wnd The receiver window.
     * @param new_size     Size of the new window.
     *
     * @return true if event was handled, false if not.
     */
    virtual bool on_resize(window& wnd, glm::ivec2 new_size) = 0;

    /**
     * Called when the application received a close window request.
     *
     * @param [in,out] wnd The receiver window.
     *
     * @return true if the window can be closed.
     */
    virtual bool on_quit(window& wnd) = 0;

    /**
     * Called when a character is pressed.
     *
     * @param [in,out] wnd The receiver window.
     * @param chr          The character.
     *
     * @return true if event was handled, false if not.
     */
    virtual bool on_char(window& wnd, char chr) = 0;

    /**
     * Called when a key is pressed.
     * 
     * This event will be repeated if the key is pressed for a long time! (TODO)
     *
     * @param [in,out] wnd The receiver window.
     * @param kc           The keycode.
     *
     * @return true if event was handled, false if not.
     */
    virtual bool on_keydown(window& wnd, keycode kc) = 0;

    /**
     * Called when a key is released
     *
     * @param [in,out] wnd The receiver window.
     * @param kc           The keycode.
     *
     * @return true if event was handled, false if not.
     */
    virtual bool on_keyup(window& wnd, keycode kc) = 0;

    virtual bool on_mousemove(window& wnd, glm::ivec2 coord) = 0;

    virtual bool on_mousedown(window& wnd, glm::ivec2 coord, mouse_button btn) = 0;

    virtual bool on_mouseup(window& wnd, glm::ivec2 coord, mouse_button btn) = 0;

    void move_mouse_to(window& wnd, glm::ivec2 coord) {
      wnd.move_cursor_to(coord);
    }

   protected:
    std::unique_ptr<program_arguments> program_args;
    std::unique_ptr<asset_loader> assets;
};
}