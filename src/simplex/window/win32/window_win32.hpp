
#pragma once

#include <Windows.h>

#include "simplex/window/window.hpp"

#ifdef WIN32

namespace simplex {

/// <summary>	A win32 window. </summary>
class win32_window : public window {
   public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Creates a new window. </summary>
    ///
    /// <param name="owner_application">	[in,out] Reference to the running application. </param>
    /// <param name="title">				The window's title. </param>
    /// <param name="width">				The window's width. </param>
    /// <param name="height">				The window's height. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    win32_window(application& owner_application, std::wstring title, unsigned int width, unsigned int height);

    /// <summary>	Destructor. </summary>
    virtual ~win32_window();

    virtual bool is_running();

    virtual void show();

    virtual void swap_buffers();

   protected:
    HWND handle;
};
}

#endif