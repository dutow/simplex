
#pragma once

#include <string>

#include "simplex/error/simplex_error.hpp"

namespace simplex {
/// <summary>	An error with a reason inside the application. </summary>
class application_error : public simplex_error {
   public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Constructor. </summary>
    ///
    /// <param name="errorMsg">	Message describing the error. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    application_error(const std::string error_msg) : simplex_error(error_msg) {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Writes the exception message to the log </summary>
    ///
    /// <param name="os">	[in,out] Log output stream. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void log(el::base::type::ostream_t& os) const {
        os << "Application error: " << error_msg;
    }
};
}