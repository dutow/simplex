
#pragma once

#include <memory>
#include <string>

namespace simplex {

class application;

class window {
   public:
    static std::unique_ptr<window> create(application& owner_application, std::wstring title, unsigned int width, unsigned int height);

    virtual ~window(){};

    virtual bool is_running() = 0;

    virtual void show() = 0;

    virtual void swap_buffers() = 0;

    std::wstring get_title() const { return title; }
    unsigned int get_width() const { return width; }
    unsigned int get_height() const { return height; }

   protected:
    window(application& owner_application, std::wstring title, unsigned int width, unsigned int height)
        : owner_application(owner_application), title(title), width(width), height(height){};

    virtual void create_window() = 0;

    application& owner_application;

    std::wstring title;
    unsigned int width;
    unsigned int height;

   private:
    window& operator=(window const& other);
};
}