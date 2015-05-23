
#pragma once

// TODO: make it more generic!

#include <GL/glew.h>
#include <boost/core/noncopyable.hpp>

#include "simplex/assets/asset_loader.hpp"


namespace simplex {

  class texture : private boost::noncopyable {
  public:
    enum class mode { T_2D, CUBEMAP };

    enum class unit {
      UNIT0 = GL_TEXTURE0,
      UNIT1 = GL_TEXTURE1
    };

    texture(asset_loader const& assets, asset_loader::path texture_path, mode texture_mode);
    ~texture();
    
    void bind(unit u);

  private:
    mode texture_mode;

    uint32_t texture_id;
  };

}