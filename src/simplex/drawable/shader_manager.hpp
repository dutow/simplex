
#pragma once

#include <map>
#include <memory>

#include "simplex/drawable/shader.hpp"
#include "simplex/assets/asset_loader.hpp"

namespace simplex {
/// <summary>	Manager for shaders. Has method to add/lookup them based on their location. </summary>
class shader_manager {
   public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Constructor. </summary>
    ///
    /// <param name="assets">	Asset loader used by the manager. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    shader_manager(asset_loader const& assets);
    /// <summary>	Destructor. </summary>
    virtual ~shader_manager();

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Loads and adds a shader. </summary>
    ///
    /// <param name="location">	The location of it's files. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void add_shader(asset_loader::path const location);

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Query if the manager has a shader with the given location. </summary>
    ///
    /// <param name="location">	The location of the shader. </param>
    ///
    /// <returns>	true if exists, false if not. </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    bool has_shader(asset_loader::path const location) const;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Removes the shader described by location. </summary>
    ///
    /// <param name="location">	The location. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void remove_shader(asset_loader::path const location);

    /// <summary>	Removes and destroys all shaders from the manager. </summary>
    void clear();

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Array indexer operator, returns a shader or throws an exception. </summary>
    ///
    /// <param name="location">	The location of the shader. </param>
    ///
    /// <returns>	The shader. </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    shader& operator[](asset_loader::path const location) const;

   private:
    asset_loader const& assets;

    std::map<asset_loader::path, std::unique_ptr<shader>> shaders;
};
}