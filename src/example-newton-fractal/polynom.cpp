
#include "polynom.hpp"

#include <easylogging++.h>
#include <glm/geometric.hpp>

#include "simplex/error/application_error.hpp"

polynom::polynom(glm::ivec2 canvas_size) : canvas_size(canvas_size), colors({ glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(1, 1, 0), glm::vec3(1, 0, 1), glm::vec3(0, 1, 1), glm::vec3(1, 0.5f, 0), glm::vec3(1, 0, 0.5f), glm::vec3(0, 1, 0.5f), glm::vec3(0.5f, 1, 0), glm::vec3(0.5f, 0, 1), glm::vec3(0, 0.5f, 1) })
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

		roots[i].x += velocities[i].x * (elapsed_microseconds / 1000000.0f);
		roots[i].y += velocities[i].y * (elapsed_microseconds / 1000000.0f);
	}

	const int root_radius = 10;

	for (int i = 0; i < roots.size() - 1; i++) {
		auto& root_i = roots[i];
		auto& velocity_i = velocities[i];
		for (int j = i + 1; j < roots.size(); j++) {
			auto& root_j = roots[j];
			auto& velocity_j = velocities[j];

			if (abs(root_i.x - root_j.x) <= 2 * root_radius || abs(root_i.y - root_j.y) <= 2 * root_radius) {
				if (glm::distance(root_i, root_j) <= 2 * root_radius) {
					// we collided! masses are the same, that means they switch speed components
					auto tmp = velocity_i;
					velocity_i.x = velocity_j.x;
					velocity_i.y = velocity_j.y;
					velocity_j.x = tmp.x;
					velocity_j.y = tmp.y;

					// fix positions
					root_i.x += velocity_i.x * (elapsed_microseconds / 1000000.0f);
					root_i.y += velocity_i.y * (elapsed_microseconds / 1000000.0f);
					root_j.x += velocity_j.x * (elapsed_microseconds / 1000000.0f);
					root_j.y += velocity_j.y * (elapsed_microseconds / 1000000.0f);
				}
			}
		}
	}

	for (int i = 0; i < roots.size(); i++) {
		// wall collisions : walls are vertical or horizontal, so speedcomponent * -1 is a good answer
		if (roots[i].x < 10) {
			roots[i].x *= -1;
			roots[i].x += 20;
			velocities[i].x *= -1;
		}
		if (roots[i].x > (canvas_size.x-10)) {
			roots[i].x *= -1;
			roots[i].x += 2*(canvas_size.x-10);
			velocities[i].x *= -1;
		}
		
		
		if (roots[i].y < 10) {
			roots[i].y *= -1;
			roots[i].y += 20;
			velocities[i].y *= -1;
		}
		if (roots[i].y > canvas_size.y-10) {
			roots[i].y *= -1;
			roots[i].y += 2 * (canvas_size.y-10);
			velocities[i].y *= -1;
		}
	}
}

void polynom::randomize()
{
	roots.clear();
	velocities.clear();

	//int no_roots = rand() % 13 + 3;
	int no_roots = rand(3) + 3;

	for (int i = 0; i < no_roots; i++) {
		add_random_root();
	}
}

void polynom::add_random_root()
{
	int max_l = canvas_size.x > canvas_size.y ? canvas_size.x : canvas_size.y;
	int max_speed = max_l / 10;
	int base = max_speed * 2 * 10;

	if (velocities.size() >= 12) {
		return;
	}
	velocities.push_back(glm::vec2(rand(base) / 10.0f - 10.0f, rand(base) / 10.0f - 10.0f));
	roots.push_back(glm::vec2(rand(canvas_size.x), rand(canvas_size.y)));
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

int polynom::rand(int max)
{
	return std::uniform_int_distribution<>(0, max)(eng);
}


