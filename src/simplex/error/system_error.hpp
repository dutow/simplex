
#pragma once

#include <exception>

namespace simplex {
class system_error : public std::exception {
   public:
    system_error(const std::string errorMsg) : errorMsg(errorMsg) {}

    std::string const& getError() const { return errorMsg; }

   protected:
    const std::string errorMsg;

   private:
    system_error& operator=(const system_error&);
};
}