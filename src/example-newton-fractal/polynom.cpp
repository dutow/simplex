
#include "polynom.hpp"

#include <easylogging++.h>

#include "simplex/error/application_error.hpp"

polynom::polynom(std::vector<glm::vec2> roots) : roots(roots), colors({ glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0,0,1) })
{
	if (roots.size() > 16) {
		auto exc = new simplex::application_error("Too many polygon roots, maximum is 16");
		LOG(FATAL) << *exc;
		throw exc;
	}
	// TODO: computed parts!
}

polynom::~polynom()
{

}

void polynom::modify(simplex::shader& target)
{
	target.uniform_vec2fv("roots", roots);
	target.uniform_vec3fv("colors", colors);
	target.uniform_int("no_roots", static_cast<int>(roots.size()));
}

