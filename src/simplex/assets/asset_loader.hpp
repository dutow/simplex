
#pragma once

#include <string>
#include <memory>
#include <boost/filesystem/path.hpp>
#include <boost/function.hpp>
#include <iostream>


#include "simplex/application/program_arguments.hpp"

namespace simplex {


/** Interface for asset loaders. */
class asset_loader {
   public:

	   /** Defines an alias representing the path of an asset. */
	   typedef boost::filesystem::path path;

  /**
   * Defines the functor type for asset_loader constructors.
   *
   * ### remarks Some (most) asset loaders require program arguments for their construction (for
   * example, the location of the executable), but those parameters are not available in the
   * initializer list, thanks to program_arguments being there as a unique_ptr. To circumvent this
   * problem, the application constructor instead requires this type, which can be called after
   * program_arguments is set.
   */
	typedef boost::function<std::unique_ptr<asset_loader>(program_arguments const& x)> constructor;

    /** Default constructor. */
    asset_loader() {}
    /** Destructor. */
    virtual ~asset_loader() {}

  /**
   * Queries if a given asset exists.
   *
   * @param asset_name Name of the asset.
   *
   * @return true if it exists, false if not.
   */
	virtual bool asset_exists(boost::filesystem::path asset_name)  const = 0;

  /**
   * Loads an asset.
   *
   * @param asset_name Name of the asset.
   * @param mode       The read mode (for binary files).
   *
   * @return The asset's content as a string.
   */
	virtual std::string load_asset(boost::filesystem::path asset_name, std::ios_base::openmode mode = std::ios_base::in)  const = 0;

  /**
   * Loads a binary asset.
   *
   * @param asset_name Name of the asset.
   *
   * @return The binary asset in memory.
   */
  virtual std::vector<uint8_t> load_binary_asset(boost::filesystem::path asset_name) const = 0;

};
}