
#pragma once

#include <vector>
#include <cstdint>
#include <random>
#include <chrono>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "simplex/drawable/shader.hpp"
#include "simplex/drawable/uniform_object.hpp"


class polynom : public simplex::uniform_object {
public:
	polynom(glm::ivec2 canvas_size);
	~polynom();

	virtual void modify(simplex::shader& target);

	void update(uint64_t elapsed_microseconds);

	void resize_canvas(glm::ivec2 new_size);

	void randomize();

	void add_random_root();

private:
	std::vector<glm::vec2> roots;
	std::vector<glm::vec2> velocities;
	std::vector<glm::vec3> colors;

	glm::ivec2 canvas_size;

	int rand(int max);

	// RNG state
	std::mt19937 eng{ static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()) };

};