
#pragma once

#include <map>
#include <memory>

#include "simplex/drawable/shader.hpp"
#include "simplex/drawable/asset_manager.hpp"

namespace simplex {
/** Manager for shaders. Has method to add/lookup them based on their location. */
class shader_manager : public asset_manager<shader> {
   public:
    typedef asset_manager<shader> base_type;
    shader_manager(asset_loader const& loader);

    void add(asset_loader::path const location);
};
}