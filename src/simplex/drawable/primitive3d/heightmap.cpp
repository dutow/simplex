
#include "heightmap.hpp"

#include "easylogging++.h"

#include <vector>
#include <GL/glew.h>
#include <glm/vec3.hpp>

namespace simplex {
  namespace primitive3d {
    heightmap::heightmap() {

      // first iteration: a simple, big quad, y-up
      static const float s = 2.0f;
      static const float z = 0.0f;
      std::vector<glm::vec3> vertex_buffer(6);
      vertex_buffer[0] = glm::vec3(z, z, z);
      vertex_buffer[1] = glm::vec3(z, z, s);
      vertex_buffer[2] = glm::vec3(s, z, s);

      vertex_buffer[3] = glm::vec3(s, z, s);
      vertex_buffer[4] = glm::vec3(s, z, z);
      vertex_buffer[5] = glm::vec3(z, z, z);

      glGenVertexArrays(1, &vao_id);
      glBindVertexArray(vao_id);

      glGenBuffers(1, &vbo_id);
      glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
      glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(float), &vertex_buffer[0], GL_STATIC_DRAW);

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    void heightmap::render() {
      glBindVertexArray(vao_id);
      glDrawArrays(GL_TRIANGLES, 0, 6);
    }
  }
}