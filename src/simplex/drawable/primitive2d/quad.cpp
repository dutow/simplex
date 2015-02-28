
#include "quad.hpp"

#include "easylogging++.h"

#include <vector>
#include <GL/glew.h>
#include <glm/vec3.hpp>

namespace simplex {
namespace primitive2d {
quad::quad(glm::vec2 top_left, glm::vec2 bottom_right) {
    std::vector<glm::vec2> vertex_buffer(6);
    vertex_buffer[0] = glm::vec2(top_left.x, top_left.y);
    vertex_buffer[1] = glm::vec2(top_left.x, bottom_right.y);
    vertex_buffer[2] = glm::vec2(bottom_right.x, bottom_right.y);
    vertex_buffer[3] = glm::vec2(bottom_right.x, bottom_right.y);
    vertex_buffer[4] = glm::vec2(bottom_right.x, top_left.y);
    vertex_buffer[5] = glm::vec2(top_left.x, top_left.y);

	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

    glGenBuffers(1, &vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), &vertex_buffer[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void quad::render() {
	glBindVertexArray(vao_id);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
}
}