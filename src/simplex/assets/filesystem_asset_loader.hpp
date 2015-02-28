
#pragma once

#include "simplex/assets/asset_loader.hpp"

#include <memory>
#include <boost/filesystem/path.hpp>

namespace simplex {

/// <summary>	A filesystem based asset loader. Loads files relative from a root directory.</summary>
class filesystem_asset_loader : public asset_loader {
   public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Constructor. </summary>
    ///
    /// <param name="root_path">	Path of the root directory. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	   filesystem_asset_loader(boost::filesystem::path root_path);

	virtual bool asset_exists(boost::filesystem::path asset_name)  const override;

	virtual std::string load_asset(boost::filesystem::path asset_name, std::ios_base::openmode mode = std::ios_base::in)  const override;

   private:
    boost::filesystem::path root_path;
};
}