
#include "plane.hpp"

#include <vector>

namespace simplex {
  namespace primitive2d{


    plane::plane(glm::vec2 top_left, glm::vec2 bottom_right, glm::ivec2 steps)
    {
      glm::vec2 size = bottom_right - top_left;
      glm::vec2 step(size.x / steps.x, size.y / steps.y);

      std::vector<glm::vec2> vertices(steps.x * steps.y);

      for (int iy = 0; iy < steps.y; ++iy) {
        for (int ix = 0; ix < steps.x; ++ix) {
          vertices[iy * steps.x + ix] = top_left + glm::vec2(step.x*ix, step.y*iy);
        }
      }

      std::vector<uint16_t> indices((steps.y-1) * (steps.x + 2) * 2);

      int i = 0;
      for (int iy = 0; iy < steps.y - 1; ++iy) {
        if (iy != 0) { // degenerate
          indices[i++] = iy * steps.x;
        }
        for (int ix = 0; ix < steps.x; ++ix) {
          indices[i++] = iy * steps.x + ix;
          indices[i++] = (iy+1) * steps.x + ix;
        }
        if (iy != steps.y - 2) { // degenerate
          indices[i++] = (iy + 1) * steps.x + (steps.x - 1);
        }
      }
      indices.resize(i);
      index_count = i;

      glGenVertexArrays(1, &vao_id);
      glBindVertexArray(vao_id);

      glGenBuffers(1, &vertex_vbo_id);
      glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo_id);
      glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);

      glGenBuffers(1, &index_vbo_id);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_vbo_id);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint16_t), &indices[0], GL_STATIC_DRAW);

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo_id);
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    void plane::render()
    {
      glBindVertexArray(vao_id);
      glDrawElements(GL_TRIANGLE_STRIP, index_count, GL_UNSIGNED_SHORT, 0);

    }

  }
}