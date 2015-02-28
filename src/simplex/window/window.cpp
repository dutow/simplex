
#include "window.hpp"

#include "simplex/window/win32/window_win32.hpp"

namespace simplex {

std::unique_ptr<window> window::create(application& owner_application, std::wstring title, unsigned int width, unsigned int height) {
#ifdef WIN32
    return std::move(std::unique_ptr<window>(new win32_window(owner_application, title, width, height)));

#endif
}
}