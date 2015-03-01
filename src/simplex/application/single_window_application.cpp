////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	G:\cppdev\simplex\src\simplex\application\single_window_application.cpp
//
// summary:	Implements the single window application class
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "single_window_application.hpp"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "simplex/window/window.hpp"



namespace simplex {

single_window_application::single_window_application(std::wstring title, unsigned int width, unsigned int height,
    std::unique_ptr<program_arguments> program_args, asset_loader::constructor asset_loader_constructor)
    : application(std::move(program_args), asset_loader_constructor), orthogonal_projection_screensize(glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height))), orthogonal_projection_01(glm::ortho(0.0f, 1.0f, 0.0f, 1.0f)), application_window(window::create(*this, title, width, height))
{
}

void single_window_application::run() {
    application_window->show();
    while (application_window->is_running()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

        render();

        application_window->swap_buffers();
    }
}

single_window_application::~single_window_application() {}

bool single_window_application::on_resize(glm::ivec2 new_size)
{
    glViewport(0, 0, new_size.x, new_size.y);
    orthogonal_projection_screensize = glm::ortho(0.0f, static_cast<float>(new_size.x), 0.0f, static_cast<float>(new_size.y));
    return true;
}

}