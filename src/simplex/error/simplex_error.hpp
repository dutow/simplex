
#pragma once

#include <exception>

#include "easylogging++.h"

namespace simplex {
/// <summary>	An error in the application. </summary>
class simplex_error : public std::exception, public el::Loggable {
   public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Constructor. </summary>
    ///
    /// <param name="errorMsg">	Message describing the error. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    simplex_error(const std::string error_msg) : error_msg(error_msg) {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Gets the error message. </summary>
    ///
    /// <returns>	The error message. </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    std::string const& get_error() const { return error_msg; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Writes the exception message to the log </summary>
    ///
    /// <param name="os">	[in,out] Log output stream. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void log(el::base::type::ostream_t& os) const {
        os << "Simplex error: " << error_msg;
    }

   protected:
    const std::string error_msg;

   private:
    simplex_error& operator=(const simplex_error&);
};
}