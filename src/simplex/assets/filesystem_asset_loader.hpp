
#pragma once

#include "simplex/assets/asset_loader.hpp"

#include <memory>
#include <boost/filesystem/path.hpp>

namespace simplex {

/** A filesystem based asset loader. Loads files relative from a root directory. */
class filesystem_asset_loader : public asset_loader {
   public:
     /**
      * Constructor.
      *
      * @param root_path Path of the root directory.
      */
	   filesystem_asset_loader(boost::filesystem::path root_path);

	virtual bool asset_exists(boost::filesystem::path asset_name)  const override;

	virtual std::string load_asset(boost::filesystem::path asset_name, std::ios_base::openmode mode = std::ios_base::in)  const override;

  virtual std::vector<uint8_t> load_binary_asset(boost::filesystem::path asset_name) const override;

   private:
    boost::filesystem::path root_path;
};
}