
#include "texture_manager.hpp"

namespace simplex {


  texture_manager::texture_manager(asset_loader const& loader) : base_type(loader)
  {

  }

  void texture_manager::add(asset_loader::path const location, texture::mode tmode)
  {
    assets[location] = std::make_unique<texture>(loader, location, tmode);
  }

}