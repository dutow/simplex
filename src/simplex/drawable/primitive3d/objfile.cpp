
#include "objfile.hpp"

#include <vector>
#include <sstream>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


namespace simplex {
  struct vertex
  {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
  };


  namespace primitive3d {

    objfile::objfile(std::string content)
    {
      std::vector<glm::vec3> vertices;
      std::vector<glm::vec2> texcoords;
      std::vector<glm::vec3> normals;
      std::vector<uint16_t> indices;
      std::istringstream is(content);

      std::vector<vertex> real_vertices;

      std::string line;
      while (std::getline(is, line)) {
        if (line.substr(0, 2) == "v ") {
          std::istringstream s(line.substr(2));
          glm::vec3 v; s >> v.x; s >> v.y; s >> v.z;
          vertices.push_back(v);
        }
        else if (line.substr(0, 3) == "vt ") {
          std::istringstream s(line.substr(2));
          glm::vec2 v; s >> v.x; s >> v.y;
          texcoords.push_back(v);
        }
        else if (line.substr(0, 3) == "vn ") {
          std::istringstream s(line.substr(2));
          glm::vec3 v; s >> v.x; s >> v.y; s >> v.z;
          normals.push_back(v);
        }
        else if (line.substr(0, 2) == "f ") {
          std::istringstream s(line.substr(2));
          for (int i = 0; i < 3; i++) {
            uint16_t pos = 0, tc = 0, norm = 0; // all zero indexed!
            s >> pos;

            if ('/' == s.peek()) {
              s.ignore();
              if ('/' != s.peek()) {
                s >> tc;
              }
              if ('/' == s.peek()) {
                s.ignore();
                s >> norm;
              }

            }
            vertex v{ vertices[pos - 1] };
            if (tc > 0) v.texcoord = texcoords[tc - 1];
            if (norm > 0) v.normal = normals[norm - 1];
            real_vertices.push_back(v);
          }
        }
        else if (line[0] == '#') { /* ignoring this line */ }
        else { /* ignoring this line */ }
      }

      glGenVertexArrays(1, &vao_id);
      glBindVertexArray(vao_id);

      glGenBuffers(1, &vbo_id);
      glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
      glBufferData(GL_ARRAY_BUFFER, real_vertices.size() * sizeof(vertex), &real_vertices[0], GL_STATIC_DRAW);

      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(sizeof(glm::vec3)));
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(sizeof(glm::vec3) * 2));

      size = static_cast<uint16_t>(real_vertices.size());
    }


    void objfile::render() {
      glBindVertexArray(vao_id);
      glDrawArrays(GL_TRIANGLES, 0, size);
    }
  }
}