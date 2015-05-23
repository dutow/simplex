
#pragma once

#include <memory>
#include <string>

#include <glm/vec2.hpp>

namespace simplex {

class application;


/** Represents a mouse button.  
 * TODO: handle many button mouse better? 
 */
enum class mouse_button { LEFT, MIDDLE, RIGHT, X1, X2 };

/** A window. */
class window {
   public:
    /**
     * Creates a new window, based on the platform.
     *
     * @param [in,out] owner_application Reference to the running application.
     * @param title                      The window's title.
     * @param width                      The window's width.
     * @param height                     The window's height.
     *
     * @return A new window.
     */
    static std::unique_ptr<window> create(application& owner_application, std::wstring title, unsigned int width, unsigned int height);

    /** Destructor. */
    virtual ~window(){};

    /**
     * Tells if this object is running, true until it gets closed.
     *
     * @return true if running, false if not.
     */
    virtual bool is_running() = 0;

    /** Shows this window. */
    virtual void show() = 0;

    /** Swaps the OpenGL buffers, displaying the content rendered before this call. */
    virtual void swap_buffers() = 0;

    /**
     * Move cursor to the given window relative coordinates.
     *
     * @param coord The coordinate.
     */
    virtual void move_cursor_to(glm::ivec2 coord) = 0;

    /**
     * Returns the window's title.
     *
     * @return The title.
     */
    std::wstring get_title() const { return title; }

    /**
     * Returns the window's width.
     *
     * @return The width.
     */
    unsigned int get_width() const { return width; }

    /**
     * Returns the window's height.
     *
     * @return The height.
     */
    unsigned int get_height() const { return height; }

	application& get_application() { return owner_application; }


   protected:
    /**
     * Protected constructor, to be used by descendants. Should create a new window.
     *
     * @param [in,out] owner_application Reference to the running application.
     * @param title                      The window's title.
     * @param width                      The window's width.
     * @param height                     The window's height.
     */
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