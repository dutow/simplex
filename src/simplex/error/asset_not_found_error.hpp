
#pragma once

#include <string>

#include "simplex/error/simplex_error.hpp"

namespace simplex {
class asset_not_found_error : public simplex_error {
   public:
    /**
     * Constructor.
     *
     * @param asset_name Name of the asset.
     */
    asset_not_found_error(const std::string asset_name) : simplex_error(asset_name) {}

    /**
     * Writes the exception message to the log.
     *
     * @param [in,out] os Log output stream.
     */
    virtual void log(el::base::type::ostream_t& os) const { os << "Asset not found error: " << error_msg; }
};
}