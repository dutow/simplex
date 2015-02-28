
#pragma once

#include <string>
#include <memory>

#include "simplex/application/application.hpp"

namespace simplex {

class window;

/// <summary>	Implements a simple single window application. </summary>
class single_window_application : public application {
   public:
	   ////////////////////////////////////////////////////////////////////////////////////////////////////
	   /// <summary>	Constructor. </summary>
	   ///
	   /// <param name="title">		  	The window's title. </param>
	   /// <param name="width">		  	The window's width. </param>
	   /// <param name="height">	  	The window's height. </param>
	   /// <param name="program_args">	The program arguments. </param>
	   /// <param name="assets">	  	The asset factory. </param>
	   ////////////////////////////////////////////////////////////////////////////////////////////////////
	   single_window_application(std::wstring title, unsigned int width, unsigned int height, std::unique_ptr<program_arguments> program_args, asset_loader::constructor asset_loader_constructor = SIMPLEX_MAGIC_ASSET);

    /// <summary>	Destructor. </summary>
    virtual ~single_window_application();

    /// <summary>	Runs the main loop of the application. </summary>
    virtual void run();

   protected:
    /// <summary>	Renders the scene. </summary>
    virtual void render() = 0;

   private:
    std::unique_ptr<window> application_window;
};
}