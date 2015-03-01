
#pragma once

#include <map>
#include <memory>
#include <string>

#include "simplex/drawable/drawable.hpp"

namespace simplex {

/// <summary>	Manager for drawable classes. Has method to add/lookup them based on their internal name. </summary>
class drawable_manager {
   public:
    /// <summary>	Default constructor. </summary>
    drawable_manager();

    /// <summary>	Destructor. </summary>
    virtual ~drawable_manager();

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Adds a drawable to this manager. </summary>
    ///
    /// <remarks>	If name already exists, it overwrites it. </remarks>
    ///
    /// <param name="name">	   	The internal lookup name. </param>
    /// <param name="drawable">	The drawable. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void add_drawable(std::string const name, std::unique_ptr<drawable> drawable);

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Query if the manager has a drawable with the given name. </summary>
    ///
    /// <param name="name">	The name of the drawable. </param>
    ///
    /// <returns>	true if found, false if not. </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    bool has_drawable(std::string const name) const;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Removes the drawable described by name. </summary>
    ///
    /// <remarks>	No exception if it doesn't exists, for now. Call it undefined behaviour? </remarks>
    ///
    /// <param name="name">	The name of a drawable. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void remove_drawable(std::string const name);

    /// <summary>	Removes (and thus destroys) all drawable classes. </summary>
    void clear();

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Array indexer operator, returns a drawable or throws an exception. </summary>
    ///
    /// <param name="name">	The name of the drawable. </param>
    ///
    /// <returns>	The drawable. </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    drawable& operator[](std::string const name) const;

   private:
    std::map<std::string, std::unique_ptr<drawable>> drawables;
};
}