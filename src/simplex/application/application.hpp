
#pragma once

#include <memory>
#include <glm/vec2.hpp>

#include "simplex/assets/magic_asset_loader.hpp"
#include "simplex/application/program_arguments.hpp"

namespace simplex {

	class window;

/// <summary>	Minimal class representing an application. </summary>
class application {
   public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Initializes the application. </summary>
    ///
    /// <param name="program_args">	The program arguments. </param>
    /// <param name="assets">	  	The asset factory. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    application(std::unique_ptr<program_arguments> program_args, asset_loader::constructor asset_loader_constructor)
        : program_args(std::move(program_args)), assets(std::move(asset_loader_constructor(get_program_args()))){};

    /// <summary>	Destructor. </summary>
    virtual ~application(){};

    /// <summary>	Runs the main loop of the application. </summary>
    virtual void run() = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Returns the program arguments. </summary>
    ///
    /// <returns>	The program arguments. </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    program_arguments const& get_program_args() const { return *program_args; }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Called when the window is resizd. </summary>
	///
	/// <param name="wnd">	   	[in,out] The receiver window. </param>
	/// <param name="new_size">	Size of the new window. </param>
	///
	/// <returns>	true if event was handled, false if not. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool on_resize(window& wnd, glm::ivec2 new_size) = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Called when the application received a close window request. </summary>
	///
	/// <param name="wnd">	[in,out] The receiver window. </param>
	///
	/// <returns>	true if the window can be closed. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool on_quit(window& wnd) = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Called when a character is pressed. </summary>
	///
	/// <param name="wnd">	[in,out] The receiver window. </param>
	/// <param name="chr">	The character. </param>
	///
	/// <returns>	true if event was handled, false if not. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool on_char(window& wnd, char chr) = 0;



   protected:
    std::unique_ptr<program_arguments> program_args;
    std::unique_ptr<asset_loader> assets;
};
}