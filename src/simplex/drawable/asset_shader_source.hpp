
#pragma once

#include <easylogging++.h>

#include "simplex/drawable/shader_source.hpp"
#include "simplex/assets/asset_loader.hpp"

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
    asset_shader_source(asset_loader const& assets, asset_loader::path parent_path);
    
    /** Destructor. */
    virtual ~asset_shader_source();

    virtual std::string name();

    virtual std::string vertex_shader();
    virtual std::string fragment_shader();

  private:
    asset_loader const& assets;
    asset_loader::path parent_path;

    /**
     * Loads the file, and processes some custom preprocessor directives - currently only #include.
     * 
     * Supports: #include "a.glsl" - relative, "/a.glsl" - from asset root
     * 
     * TODO #pragma once
     *
     * @param asset_path Full pathname of the asset file.
     */
    std::string  process_file(asset_loader::path asset_path) const;

    asset_loader::path lookup_file(asset_loader::path source, std::string name) const;
  };
}