
#pragma once

#include <Windows.h>

#include "simplex/window/window.hpp"

#ifdef WIN32

namespace simplex {

/** A win32 window. */
class win32_window : public window {
   public:
    /**
     * Creates a new window.
     *
     * @param [in,out] owner_application Reference to the running application.
     * @param title                      The window's title.
     * @param width                      The window's width.
     * @param height                     The window's height.
     */
    win32_window(application& owner_application, std::wstring title, unsigned int width, unsigned int height);

    /** Destructor. */
    virtual ~win32_window();

    virtual bool is_running();

    virtual void show();

    virtual void swap_buffers();

    virtual void move_cursor_to(glm::ivec2 coord);

   protected:
    HWND handle;
};
}

#endif