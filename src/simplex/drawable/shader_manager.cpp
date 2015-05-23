
#include "shader_manager.hpp"

#include "simplex/drawable/asset_shader_source.hpp"

namespace simplex {

  void shader_manager::add(asset_loader::path const location)
  {
    assets[location] = std::make_unique<shader>(std::make_unique<asset_shader_source>(loader, location));
  }

  shader_manager::shader_manager(asset_loader const& loader) : base_type(loader)
  {

  }

}
