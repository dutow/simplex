
#include "sphere.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <easylogging++.h>

namespace simplex {
  namespace primitive3d {


    sphere::sphere(float radius, uint16_t rings, uint16_t sectors)
    {
      const float M_PI = 3.14f;
      const float M_PI_2 = 6.28f;

      std::vector<glm::vec3> vertices(rings * sectors);
      std::vector<glm::vec3> normals(rings * sectors);
      std::vector<glm::vec2> texcoords(rings * sectors);
      std::vector<uint16_t> indices(rings * sectors * 6);

      float const R = 1.0f / (float)(rings - 1);
      float const S = 1.0f / (float)(sectors - 1);

      int r, s;

      std::vector<glm::vec3>::iterator v = vertices.begin();
      std::vector<glm::vec3>::iterator n = normals.begin();
      std::vector<glm::vec2>::iterator t = texcoords.begin();

      for (r = 0; r < rings; r++) {
        float y = sin(M_PI * r * R);

        for (s = 0; s < sectors; s++) {
          float x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
          float z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

          t->x = s*S;
          t->y = r*R;
          t++;

          v->x = x*radius;
          v->y = y*radius;
          v->z = z*radius;
          v++;

          n->x = x;
          n->y = y;
          n->z = z;
          n++;
        }
      }

      std::vector<uint16_t>::iterator i = indices.begin();

      for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
        *i++ = r * sectors + s;
        *i++ = r * sectors + (s + 1);
        *i++ = (r + 1) * sectors + (s + 1);
        
        *i++ = r * sectors + s;
        *i++ = (r + 1) * sectors + (s + 1);
        *i++ = (r + 1) * sectors + s;
      }

      glGenVertexArrays(1, &vao_id);
      glBindVertexArray(vao_id);

      glGenBuffers(1, &vertex_vbo_id);
      glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo_id);
      glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
      
      glGenBuffers(1, &normal_vbo_id);
      glBindBuffer(GL_ARRAY_BUFFER, normal_vbo_id);
      glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
      
      glGenBuffers(1, &texcoord_vbo_id);
      glBindBuffer(GL_ARRAY_BUFFER, texcoord_vbo_id);
      glBufferData(GL_ARRAY_BUFFER, texcoords.size() * sizeof(glm::vec2), &texcoords[0], GL_STATIC_DRAW);

      glGenBuffers(1, &index_vbo_id);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_vbo_id);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint16_t), &indices[0], GL_STATIC_DRAW);

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo_id);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

      glEnableVertexAttribArray(1);
      glBindBuffer(GL_ARRAY_BUFFER, normal_vbo_id);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

      glEnableVertexAttribArray(2);
      glBindBuffer(GL_ARRAY_BUFFER, texcoord_vbo_id);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

      index_count = static_cast<uint16_t>(indices.size());
    }

    void sphere::render()
    {
      glBindVertexArray(vao_id);
      glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_SHORT, 0);
    }

  }
}