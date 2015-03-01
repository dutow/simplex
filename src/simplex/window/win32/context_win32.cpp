
#include "context_win32.hpp"

#include <string>
#include <ctime>
#include "easylogging++.h"
#include <GL/glew.h>
#include <GL/wglew.h>

#include "simplex/application/application.hpp"
#include "simplex/window/window.hpp"
#include "simplex/error/system_error.hpp"

namespace simplex {

context_win32::context_win32() {
    h_instance = GetModuleHandle(NULL);

    register_window_class();

    init_glew();
}

void context_win32::register_window_class() {
    WNDCLASS wc;
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = wnd_proc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = h_instance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = CLASSNAME.c_str();
    if (!RegisterClass(&wc)) {
        LOG(FATAL) << L"Couldn't register window class " << CLASSNAME;
        throw new simplex::system_error("Couldn't register window class!");
    }
}

void context_win32::init_glew() {
    HWND fake_window = CreateWindow(CLASSNAME.c_str(), L"FAKE", WS_OVERLAPPEDWINDOW | WS_MAXIMIZE | WS_CLIPCHILDREN, 0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
                                    NULL, h_instance, NULL);

    HDC hDC = GetDC(fake_window);

    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int pixel_format = ChoosePixelFormat(hDC, &pfd);
    if (pixel_format == 0) {
        LOG(FATAL) << L"Could not choose pixel format for the dummy window";
        throw new simplex::system_error("Could not choose pixel format for the dummy window");
    }

    if (!SetPixelFormat(hDC, pixel_format, &pfd)) {
        LOG(FATAL) << L"Could not set pixel format for the dummy window";
        throw new simplex::system_error("Could not set pixel format for the dummy window");
    }

    HGLRC hRC_fake = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC_fake);

    GLenum glew_err = glewInit();
    if (glew_err != GLEW_OK) {
        LOG(FATAL) << L"GLEW initialization error:" << glewGetErrorString(glew_err);
        throw new simplex::system_error("GLEW initialization error");
    }

    if (!GLEW_VERSION_3_3) {  // TODO: make OpenGL version customizable
        LOG(FATAL) << L"OpenGL 3.3 or later required";
        throw new simplex::system_error("OpenGL 3.3 or later required");
    }

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC_fake);
    DestroyWindow(fake_window);
}

context_win32::~context_win32() { UnregisterClass(CLASSNAME.c_str(), h_instance); }

context_win32& context_win32::get_instance() {
    if (instance.operator simplex::context_win32*() == nullptr) {
        std::lock_guard<std::mutex> mlock(mtx);
        if (instance.operator simplex::context_win32*() == nullptr) {
            instance = new context_win32();
        }
    }

    return *instance;
}

boolean context_win32::initialize_opengl(HWND const& window_handle) {
    LOG(TRACE) << L"Initializing OpenGL for window " << window_handle;

    HDC hDC = GetDC(window_handle);

    const int iPixelFormatAttribList[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE, WGL_SUPPORT_OPENGL_ARB, GL_TRUE, WGL_DOUBLE_BUFFER_ARB, GL_TRUE, WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32, WGL_DEPTH_BITS_ARB, 24, WGL_STENCIL_BITS_ARB, 8,
        0  // End of attributes list
    };
    int iContextAttribs[] =  // TODO: make OpenGL version customizable
        {
         WGL_CONTEXT_MAJOR_VERSION_ARB, 3, WGL_CONTEXT_MINOR_VERSION_ARB, 3, WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
         0  // End of attributes list
        };

    int iPixelFormat, iNumFormats;
    wglChoosePixelFormatARB(hDC, iPixelFormatAttribList, NULL, 1, &iPixelFormat, (UINT*)&iNumFormats);
    PIXELFORMATDESCRIPTOR pfd;  // empty...
    if (!SetPixelFormat(hDC, iPixelFormat, &pfd)) {
        LOG(FATAL) << L"Could not set pixel format for window" << window_handle;
        return false;
    }

    HGLRC hRC = wglCreateContextAttribsARB(hDC, 0, iContextAttribs);

    if (!hRC) {
        LOG(FATAL) << "Could not create context for window " << window_handle;
        return false;
    }

    wglMakeCurrent(hDC, hRC);

    LOG(DEBUG) << L"OpenGL initialized for window" << window_handle;

    return true;
}

void context_win32::swap_buffers(HWND const& window_handle) {
    HDC hDC = GetDC(window_handle);
    SwapBuffers(hDC);
}

HWND context_win32::create_window(std::wstring title, unsigned int width, unsigned int height, window* owner) {
    HWND window_handle =
        CreateWindow(CLASSNAME.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 0, 0, width, height, NULL, NULL, h_instance, owner);

    return window_handle;
}

void context_win32::show_window(HWND const& window_handle) { ShowWindow(window_handle, SW_SHOW); }

LRESULT CALLBACK context_win32::wnd_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    window* wnd = nullptr;

    if (message == WM_NCCREATE) {
        wnd = reinterpret_cast<window*>((LONG_PTR)((CREATESTRUCT*)lParam)->lpCreateParams);
		LOG(INFO) << "WM_NCCCREATE" << wnd;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)lParam)->lpCreateParams);
    } else {
        wnd = reinterpret_cast<window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    if (wnd != nullptr) {

		auto& app = wnd->get_application();

		switch (message) {
		case WM_SIZE: {
			auto window_width = static_cast<int>(LOWORD(lParam));
			auto window_height = static_cast<int>(HIWORD(lParam));
			
			
			if (app.on_resize(*wnd, glm::ivec2(window_width, window_height))) { return 0; }
		}
		case WM_CLOSE: {
			if (app.on_quit(*wnd)) {
				PostQuitMessage(0);
			}
			return 0;
		}
		case WM_CHAR: {
			if (app.on_char(*wnd, static_cast<char>(wParam))) { return 0;  }
		}
		}

    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

std::atomic<context_win32*> context_win32::instance;
std::mutex context_win32::mtx;
const std::wstring context_win32::CLASSNAME(L"SimplexWindow");  // TODO: make window class name configurable !!!
};