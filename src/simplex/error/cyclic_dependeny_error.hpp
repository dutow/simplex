
#pragma once

#include <string>

#include "simplex/error/simplex_error.hpp"

namespace simplex {
class cyclic_dependency_error : public simplex_error {
   public:
    
    cyclic_dependency_error(const std::string original_source, const std::string asset) : simplex_error("Cyclic dependency while processing " + original_source + ", cause: " + asset) {}   
};
}