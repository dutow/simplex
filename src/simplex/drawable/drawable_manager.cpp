
#include "drawable_manager.hpp"

#include <easylogging++.h>

#include "simplex/error/asset_not_found_error.hpp"

namespace simplex {

drawable_manager::drawable_manager() {}

drawable_manager::~drawable_manager() {}

void drawable_manager::add(std::string const name, std::unique_ptr<drawable> drawable) { drawables[name] = std::move(drawable); }

bool drawable_manager::has(std::string const name) const { return drawables.find(name) != drawables.end(); }

void drawable_manager::remove(std::string const name) { drawables.erase(name); }

void drawable_manager::clear() { drawables.clear(); }

drawable& drawable_manager::operator[](std::string const name) const {
    auto rec = drawables.find(name);

    if (rec == drawables.end()) {
        auto exc = new asset_not_found_error("DrawableManager." + name);  // TODO: better error
        LOG(FATAL) << exc;
        throw exc;
    }

    return *(rec->second);
}
}