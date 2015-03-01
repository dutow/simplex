
#include "polynom.hpp"

#include <easylogging++.h>

#include "simplex/error/application_error.hpp"

polynom::polynom(glm::ivec2 canvas_size) : canvas_size(canvas_size), colors({ glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(1, 1, 0), glm::vec3(1, 0, 1), glm::vec3(0, 1, 1) })
{
	randomize();
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

void polynom::update(uint64_t elapsed_microseconds)
{
	for (int i = 0; i < roots.size(); i++) {
		// wall collisions : walls are vertical or horizontal, so speedcomponent * -1 is a good answer
		roots[i].x += velocities[i].x * (elapsed_microseconds / 1000000.0f);
		if (roots[i].x < 0) {
			roots[i].x *= -1;
			velocities[i].x *= -1;
		}
		if (roots[i].x > canvas_size.x) {
			roots[i].x *= -1;
			roots[i].x += 2*canvas_size.x;
			velocities[i].x *= -1;
		}
		
		roots[i].y += velocities[i].y * (elapsed_microseconds / 1000000.0f);
		if (roots[i].y < 0) {
			roots[i].y *= -1;
			velocities[i].y *= -1;
		}
		if (roots[i].y > canvas_size.y) {
			roots[i].y *= -1;
			roots[i].y += 2 * canvas_size.y;
			velocities[i].y *= -1;
		}
	}
}

void polynom::randomize()
{
	roots.clear();
	velocities.clear();

	//int no_roots = rand() % 13 + 3;
	int no_roots = rand() % 3 + 3;

	int max_l = canvas_size.x > canvas_size.y ? canvas_size.x : canvas_size.y;
	int max_speed = max_l / 10;
	int base = max_speed * 2 * 10;

	for (int i = 0; i < no_roots; i++) {
		velocities.push_back(glm::vec2(rand() % base / 10.0f - 10.0f, rand() % base / 10.0f - 10.0f));
		roots.push_back(glm::vec2(rand() % canvas_size.x, rand() % canvas_size.y));
	}
}

void polynom::resize_canvas(glm::ivec2 new_size)
{

	// note: keeps the positions around the same, but won't change velocities
	float ratio_x = new_size.x / (float)canvas_size.x;
	float ratio_y = new_size.y / (float)canvas_size.y;

	for (int i = 0; i < roots.size(); i++) {
		roots[i].x *= ratio_x;
		roots[i].y *= ratio_y;
	}

	canvas_size = new_size;

}


