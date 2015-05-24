
#include "cube.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <easylogging++.h>

namespace simplex {
  namespace primitive3d {


    cube::cube(float length)
    {

      float  vertices[][3] = {
        { -length/2, -length/2, -length/2 },
        { -length/2, -length/2, length/2 },
        { -length/2, length/2, -length/2 },
        { -length/2, length/2, length/2 },
        { length/2, -length/2, -length/2 },
        { length/2, -length/2, length/2 },
        { length/2, length/2, -length/2 },
        { length/2, length/2, length/2 },
      };

      uint16_t  indices[] = {
        0, 1, 3,
        0, 3, 2,
        4, 6, 7, 
        4, 7, 5,
        2, 3, 7,
        2, 7, 6,
        0, 4, 5,
        0, 5, 1,
        0, 2, 6,
        0, 6, 4,
        1, 5, 7,
        1, 7, 3
      };



      glGenVertexArrays(1, &vao_id);
      glBindVertexArray(vao_id);

      glGenBuffers(1, &vertex_vbo_id);
      glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo_id);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

      //glGenBuffers(1, &texcoord_vbo_id);
      //glBindBuffer(GL_ARRAY_BUFFER, texcoord_vbo_id);
      //glBufferData(GL_ARRAY_BUFFER, texcoords.size() * sizeof(glm::vec2), &texcoords[0], GL_STATIC_DRAW);

      glGenBuffers(1, &index_vbo_id);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_vbo_id);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo_id);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

//      glBindBuffer(GL_ARRAY_BUFFER, normal_vbo_id);
     // glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

      //glBindBuffer(GL_ARRAY_BUFFER, texcoord_vbo_id);
      //glVertexAttribPointer(6, 2, GL_FLOAT, GL_FALSE, 0, 0);

      index_count = 3*6*2;
    }

    void cube::render()
    {
      glBindVertexArray(vao_id);
      glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_SHORT, 0);
    }

  }
}