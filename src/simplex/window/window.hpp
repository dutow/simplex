
#pragma once

#include <memory>
#include <string>

namespace simplex {

class application;

/// <summary>	A window. </summary>
class window {
   public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Creates a new window, based on the platform. </summary>
    ///
    /// <param name="owner_application">	[in,out] Reference to the running application. </param>
    /// <param name="title">				The window's title. </param>
    /// <param name="width">				The window's width. </param>
    /// <param name="height">				The window's height. </param>
    ///
    /// <returns>	A new window </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    static std::unique_ptr<window> create(application& owner_application, std::wstring title, unsigned int width, unsigned int height);

    /// <summary>	Destructor. </summary>
    virtual ~window(){};

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Tells if this object is running, true until it gets closed. </summary>
    ///
    /// <returns>	true if running, false if not. </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual bool is_running() = 0;

    /// <summary>	Shows this window. </summary>
    virtual void show() = 0;

    /// <summary>	Swaps the OpenGL buffers, displaying the content rendered before this call. </summary>
    virtual void swap_buffers() = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Returns the window's title. </summary>
    ///
    /// <returns>	The title. </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    std::wstring get_title() const { return title; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Returns the window's width. </summary>
    ///
    /// <returns>	The width. </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned int get_width() const { return width; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Returns the window's height. </summary>
    ///
    /// <returns>	The height. </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned int get_height() const { return height; }

	application& get_application() { return owner_application; }


   protected:
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Protected constructor, to be used by descendants. Should create a new window. </summary>
    ///
    /// <param name="owner_application">	[in,out] Reference to the running application. </param>
    /// <param name="title">				The window's title. </param>
    /// <param name="width">				The window's width. </param>
    /// <param name="height">				The window's height. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    window(application& owner_application, std::wstring title, unsigned int width, unsigned int height)
        : owner_application(owner_application), title(title), width(width), height(height){};

    application& owner_application;

    std::wstring title;
    unsigned int width;
    unsigned int height;

   private:
    window& operator=(window const& other);
};
}