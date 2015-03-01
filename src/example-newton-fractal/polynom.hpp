
#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "simplex/drawable/shader.hpp"
#include "simplex/drawable/uniform_object.hpp"


class polynom : public simplex::uniform_object {
public:
	polynom(std::vector<glm::vec2> roots);
	~polynom();

	virtual void modify(simplex::shader& target);

private:
	std::vector<glm::vec2> roots;
	std::vector<glm::vec3> colors;
};