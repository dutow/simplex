
#pragma once

#include "simplex/application/single_window_application.hpp"

namespace simplex {
  class asset_aware {

    virtual void load_assets(asset_loaders loaders) = 0;

  };
}