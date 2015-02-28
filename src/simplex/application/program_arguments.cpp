
#include "program_arguments.hpp"

#include <boost/filesystem/operations.hpp>

namespace simplex {

program_arguments::program_arguments(int argc, char* argv[])
    : executable(boost::filesystem::system_complete(boost::filesystem::path(argv[0])).parent_path()),
      executable_dir(executable.parent_path()),
      arguments(argv + 1, argv + argc) {}

boost::filesystem::path const& program_arguments::executable_path() const { return executable; }

boost::filesystem::path const& program_arguments::executable_directory() const { return executable_dir; }

std::string const& program_arguments::operator[](size_t idx) const { return arguments[idx]; }

size_t program_arguments::argument_count() const { return arguments.size(); }
}