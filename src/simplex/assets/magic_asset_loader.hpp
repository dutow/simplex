
#pragma once

#include <boost/preprocessor/facilities/is_empty.hpp>

#include "simplex/assets/filesystem_asset_loader.hpp"
#include "simplex/application/program_arguments.hpp"

namespace simplex {

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// A magic asset constructor. Creates an asset loader that might be relative or absolute to the
/// executable directory.
/// </summary>
///
/// <remarks>
/// The idea behind this constructor is to force assets to be relative to the executable during a
/// production build, and at &lt;source_root&gt;/assets during development. With a simple cmake
/// defined macro, this does exactly that.
/// </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
struct magic_asset_constructor {
    const char* path;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Constructor. </summary>
    ///
    /// <param name="s">	CMake provided path. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    magic_asset_constructor(const char* s) : path(s) {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Creates a new asset_loader. </summary>
    ///
    /// <param name="args">	The program arguments. </param>
    ///
    /// <returns>	A new asset loader. </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    std::unique_ptr<asset_loader> operator()(program_arguments const& args) {
        if (path[0] == '.') {
            return std::make_unique<filesystem_asset_loader>(args.executable_directory() / boost::filesystem::path(path));
        } else {  // absolute path provided, at least on windows
            return std::make_unique<filesystem_asset_loader>(boost::filesystem::path(path));
        }
    }
};
}

#if !defined(SIMPLEX_MAGIC_ASSET_LOCATION) || BOOST_PP_IS_EMPTY(SIMPLEX_MAGIC_ASSET_LOCATION)
#undef SIMPLEX_MAGIC_ASSET_LOCATION
#define SIMPLEX_MAGIC_ASSET_LOCATION "."
#endif

#ifndef SIMPLEX_MAGIC_ASSET
#define SIMPLEX_MAGIC_ASSET (simplex::asset_loader::constructor(simplex::magic_asset_constructor(SIMPLEX_MAGIC_ASSET_LOCATION)))
#endif