
#pragma once

#include <map>
#include <memory>

#include "simplex/drawable/shader.hpp"
#include "simplex/assets/asset_loader.hpp"

namespace simplex {
/** Manager for shaders. Has method to add/lookup them based on their location. */
class shader_manager {
   public:
    /**
     * Constructor.
     *
     * @param assets Asset loader used by the manager.
     */
    shader_manager(asset_loader const& assets);
    /** Destructor. */
    virtual ~shader_manager();

    /**
     * Loads and adds a shader.
     *
     * @param location The location of it's files.
     */
    void add_shader(asset_loader::path const location);

    /**
     * Query if the manager has a shader with the given location.
     *
     * @param location The location of the shader.
     *
     * @return true if exists, false if not.
     */
    bool has_shader(asset_loader::path const location) const;

    /**
     * Removes the shader described by location.
     *
     * @param location The location.
     */
    void remove_shader(asset_loader::path const location);

    /** Removes and destroys all shaders from the manager. */
    void clear();

    /**
     * Array indexer operator, returns a shader or throws an exception.
     *
     * @param location The location of the shader.
     *
     * @return The shader.
     */
    shader& operator[](asset_loader::path const location) const;

   private:
    asset_loader const& assets;

    std::map<asset_loader::path, std::unique_ptr<shader>> shaders;
};
}