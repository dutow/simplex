
#pragma once

#include <string>
#include <memory>

#include "simplex/application/application.hpp"

namespace simplex {

class window;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Implements a simple single window application. </summary>
///
/// <remarks>	Parragi Zsolt, 2015-02-27 </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class single_window_application : public application {
   public:
    single_window_application(std::wstring title, unsigned int width, unsigned int height);

    virtual ~single_window_application();

    void run();

   protected:
    virtual void render() = 0;

   private:
    std::unique_ptr<window> application_window;
};
}