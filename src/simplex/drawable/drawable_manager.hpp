
#pragma once

#include <map>
#include <memory>
#include <string>

#include "simplex/drawable/drawable.hpp"

namespace simplex {

/** Manager for drawable classes. Has method to add/lookup them based on their internal name. */
class drawable_manager {
   public:
    /** Default constructor. */
    drawable_manager();

    /** Destructor. */
    virtual ~drawable_manager();

    /**
     * Adds a drawable to this manager.
     *
     * @param name     The internal lookup name.
     * @param drawable The drawable.
     *
     * ### remarks If name already exists, it overwrites it.
     */
    void add_drawable(std::string const name, std::unique_ptr<drawable> drawable);

    /**
     * Query if the manager has a drawable with the given name.
     *
     * @param name The name of the drawable.
     *
     * @return true if found, false if not.
     */
    bool has_drawable(std::string const name) const;

    /**
     * Removes the drawable described by name.
     *
     * @param name The name of a drawable.
     *
     * ### remarks No exception if it doesn't exists, for now. Call it undefined behavior?
     */
    void remove_drawable(std::string const name);

    /** Removes (and thus destroys) all drawable classes. */
    void clear();

    /**
     * Array indexer operator, returns a drawable or throws an exception.
     *
     * @param name The name of the drawable.
     *
     * @return The drawable.
     */
    drawable& operator[](std::string const name) const;

   private:
    std::map<std::string, std::unique_ptr<drawable>> drawables;
};
}