
#pragma once

#include <string>
#include <mutex>
#include <atomic>

#include <Windows.h>

#include "simplex/window/window.hpp"

namespace simplex {

class context_win32 {
   public:
    context_win32();

    ~context_win32();

    boolean initialize_opengl(HWND const& window_handle);

    void swap_buffers(HWND const& window_handle);

    HWND create_window(std::wstring title, unsigned int width, unsigned int height, window* owner);

    void show_window(HWND const& window_handle);

    static context_win32& get_instance();

    static const std::wstring CLASSNAME;

   private:
    HINSTANCE h_instance;

    static std::mutex mtx;
    static std::atomic<context_win32*> instance;

    void register_window_class();
    void init_glew();
    static LRESULT CALLBACK wnd_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
}