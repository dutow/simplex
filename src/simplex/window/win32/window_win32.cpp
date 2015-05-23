
#include "window_win32.hpp"

#include "simplex/window/win32/context_win32.hpp"

namespace simplex {

win32_window::win32_window(application& owner_application, std::wstring title, unsigned int width, unsigned int height)
    : window(owner_application, title, width, height) {
	auto context = context_win32::get_instance();
	handle = context.create_window(title.c_str(), width, height, this);
	context.initialize_opengl(handle);
}

win32_window::~win32_window() {}

void win32_window::swap_buffers() {
    auto context = context_win32::get_instance();
    context.swap_buffers(handle);
}

void win32_window::show() {
    auto context = context_win32::get_instance();
    context.show_window(handle);
}

bool win32_window::is_running() {
    MSG msg = {0};
	bool running = true;
    while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
		if (msg.message == WM_QUIT) {
			running = false;
		}
    }

    return running;
}

void win32_window::move_cursor_to(glm::ivec2 coord)
{
  POINT p;
  p.x = coord.x;
  p.y = coord.y;
  ClientToScreen(handle, &p);
  SetCursorPos(p.x,p.y);
}

}