
#pragma once

#include <map>
#include <memory>

#include "simplex/drawable/texture.hpp"
#include "simplex/drawable/asset_manager.hpp"

namespace simplex {
  /** Manager for shaders. Has method to add/lookup them based on their location. */
  class texture_manager : public asset_manager < texture > {
  public:
    typedef asset_manager<texture> base_type;
    texture_manager(asset_loader const& loader);

    void add(asset_loader::path const location, texture::mode tmode = texture::mode::T_2D);
  };
}