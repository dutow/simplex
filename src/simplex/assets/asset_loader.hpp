
#pragma once

#include <string>
#include <memory>
#include <boost/filesystem/path.hpp>
#include <boost/function.hpp>
#include <iostream>


#include "simplex/application/program_arguments.hpp"

namespace simplex {


/// <summary>	Interface for asset loaders. </summary>
class asset_loader {
   public:

	   /// <summary>	Defines an alias representing the path of an asset. </summary>
	   typedef boost::filesystem::path path;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Defines the functor type for asset_loader constructors. </summary>
	///
	/// <remarks>
	/// Some (most) asset loaders require program arguments for their construction (for example, the
	/// location of the executable), but those parameters are not available in the initializer list,
	/// thanks to program_arguments being there as a unique_ptr. To circumvent this problem, the
	/// application constructor instead requires this type, which can be called after
	/// program_arguments is set.
	/// </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	typedef boost::function<std::unique_ptr<asset_loader>(program_arguments const& x)> constructor;

    /// <summary>	Default constructor. </summary>
    asset_loader() {}
    /// <summary>	Destructor. </summary>
    virtual ~asset_loader() {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Queries if a given asset exists. </summary>
    ///
    /// <param name="asset_name">	Name of the asset. </param>
    ///
    /// <returns>	true if it exists, false if not. </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool asset_exists(boost::filesystem::path asset_name)  const = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Loads an asset. </summary>
	///
	/// <param name="asset_name">	Name of the asset. </param>
	/// <param name="mode">		 	The read mode (for binary files). </param>
	///
	/// <returns>	The asset's content as a string. </returns>
	///
	/// ### <exception cref="simplex::asset_not_found_error">	if asset not found. </exception>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual std::string load_asset(boost::filesystem::path asset_name, std::ios_base::openmode mode = std::ios_base::in)  const = 0;

};
}