
#pragma once

#include <easylogging++.h>

#include "simplex/drawable/shader_source.hpp"
#include "simplex/assets/asset_loader.hpp"
#include "simplex/error/asset_not_found_error.hpp"

namespace simplex {

  /**
   * asset based shader source.
   *
   * ### remarks The path parameter it expects is a directory, containing files named vertex.glsl
   * and fragment.glsl.
   */
  class asset_shader_source : public shader_source {
  public:
    /**
     * Creates a new shader source based on the given strings.
     *
     * @exception exc Thrown when an exc error condition occurs.
     *
     * @param assets      An asset factory.
     * @param parent_path
     * Path of a directory containing the shader files (vertex.glsl and
     * fragment.glsl).
     */
    asset_shader_source(asset_loader const& assets, asset_loader::path parent_path) : assets(assets), parent_path(parent_path) {
      if (!assets.asset_exists(parent_path / "vertex.glsl")) {
        auto exc = new asset_not_found_error((parent_path / "vertex.glsl").string());
        LOG(FATAL) << *exc;
        throw exc;
      }
      if (!assets.asset_exists(parent_path / "fragment.glsl")) {
        auto exc = new asset_not_found_error((parent_path / "vertex.glsl").string());
        LOG(FATAL) << *exc;
        throw exc;
      }
    }
    /** Destructor. */
    virtual ~asset_shader_source(){};

    virtual std::string name() { return parent_path.string(); }

    virtual std::string vertex_shader() { return assets.load_asset(parent_path / "vertex.glsl"); }
    virtual std::string fragment_shader() { return assets.load_asset(parent_path / "fragment.glsl"); }

  private:
    asset_loader const& assets;
    asset_loader::path parent_path;
  };
}