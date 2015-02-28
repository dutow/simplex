
#pragma once

#include <exception>

namespace simplex {
/// <summary>	A system related error. </summary>
class system_error : public std::exception {
   public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Constructor. </summary>
    ///
    /// <param name="errorMsg">	Message describing the error. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    system_error(const std::string error_msg) : error_msg(error_msg) {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Gets the error message. </summary>
    ///
    /// <returns>	The error message. </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    std::string const& get_error() const { return error_msg; }

   protected:
    const std::string error_msg;

   private:
    system_error& operator=(const system_error&);
};
}