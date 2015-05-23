
#pragma once

#include <map>
#include <memory>

#include "simplex/assets/asset_loader.hpp"
#include "simplex/error/asset_not_found_error.hpp"

namespace simplex {
  /** Manager for shaders. Has method to add/lookup them based on their location. */
  template<typename T>
  class asset_manager {
  public:
    /**
    * Constructor.
    *
    * @param assets Asset loader used by the manager.
    */
    asset_manager(asset_loader const& loader);
    /** Destructor. */
    virtual ~asset_manager();
    
    /**
    * Query if the manager has an asset with the given location.
    *
    * @param location The location of the shader.
    *
    * @return true if exists, false if not.
    */
    bool has(asset_loader::path const location) const;

    /**
    * Removes the asset described by location.
    *
    * @param location The location.
    */
    void unload(asset_loader::path const location);

    /** Removes and destroys all assets from the manager. */
    void clear();

    /**
    * Array indexer operator, returns an asset or throws an exception.
    *
    * @param location The location of the asset.
    *
    * @return The asset.
    */
    T& operator[](asset_loader::path const location) const;

  protected:
    asset_loader const& loader;

    std::map<asset_loader::path, std::unique_ptr<T>> assets;
  };

  template<typename T>
  T& simplex::asset_manager<T>::operator[](asset_loader::path const location) const
  {
    auto rec = assets.find(location);

    if (rec == assets.end()) {
      auto exc = new asset_not_found_error("AssetManager." + location.string());  // TODO: better error
      LOG(FATAL) << exc;
      throw exc;
    }

    return *(rec->second);
  }

  template<typename T>
  void simplex::asset_manager<T>::clear()
  {
    assets.clear();
  }

  template<typename T>
  void simplex::asset_manager<T>::unload(asset_loader::path const location)
  {
    assets.erase(location);
  }

  template<typename T>
  bool simplex::asset_manager<T>::has(asset_loader::path const location) const
  {
    return assets.find(location) != assets.end();
  }

  template<typename T>
  simplex::asset_manager<T>::~asset_manager()
  {

  }

  template<typename T>
  simplex::asset_manager<T>::asset_manager(asset_loader const& loader) : loader(loader)
  {

  }

}