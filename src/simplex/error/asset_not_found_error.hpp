
#pragma once

#include <string>

#include "simplex/error/simplex_error.hpp"

namespace simplex {
/// <summary>	An error with a reason inside the application. </summary>
class asset_not_found_error : public simplex_error {
   public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Constructor. </summary>
    ///
    /// <param name="asset_name">	Name of the asset. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    asset_not_found_error(const std::string asset_name) : simplex_error(asset_name) {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Writes the exception message to the log </summary>
    ///
    /// <param name="os">	[in,out] Log output stream. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void log(el::base::type::ostream_t& os) const { os << "Asset not found error: " << error_msg; }
};
}