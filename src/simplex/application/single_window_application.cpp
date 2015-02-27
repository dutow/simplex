////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	G:\cppdev\simplex\src\simplex\application\single_window_application.cpp
//
// summary:	Implements the single window application class
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "single_window_application.hpp"

#include "simplex/window/window.hpp"

#include <GL/glew.h>

namespace simplex {

single_window_application::single_window_application(std::wstring title, unsigned int width, unsigned int height)
    : application_window(window::create(*this, title, width, height)) {}

void single_window_application::run() {
    application_window->show();
    while (application_window->is_running()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        render();

        application_window->swap_buffers();
    }
}

single_window_application::~single_window_application() {}
}