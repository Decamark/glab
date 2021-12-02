#ifndef _GLE_GRID
#define _GLE_GRID

#include <gle/shape.hpp>
#include <learnopengl/shader_m.h>

namespace gle
{
  class Grid : public Shape
  {
  private:
    float l, m, n;
  public:
    Grid(float d, Shader shader = Shader3dColor()) : Grid(d, d, d, shader)
    {}

    Grid(float l, float m, float n, Shader shader = Shader3dColor()) : l(l), m(m), n(n), Shape(shader)
    {
      std::vector<float> vs;
      // xy-plane
      for (float y=0.0f; y<=m; y++) {
        vs.push_back(0.0f);
        vs.push_back(y);
        vs.push_back(0.0f);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
        vs.push_back(l);
        vs.push_back(y);
        vs.push_back(0.0f);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
      }
      for (float x=0.0f; x<=l; x++) {
        vs.push_back(x);
        vs.push_back(0.0f);
        vs.push_back(0.0f);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
        vs.push_back(x);
        vs.push_back(m);
        vs.push_back(0.0f);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
      }
      // yz-plane
      for (float y=0.0f; y<=m; y++) {
        vs.push_back(0.0f);
        vs.push_back(y);
        vs.push_back(0.0f);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
        vs.push_back(0.0f);
        vs.push_back(y);
        vs.push_back(n);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
      }
      for (float z=0.0f; z<=n; z++) {
        vs.push_back(0.0f);
        vs.push_back(0.0f);
        vs.push_back(z);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
        vs.push_back(0.0f);
        vs.push_back(m);
        vs.push_back(z);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
      }
      // zx-plane
      for (float z=0.0f; z<=n; z++) {
        vs.push_back(0.0f);
        vs.push_back(0.0f);
        vs.push_back(z);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
        vs.push_back(l);
        vs.push_back(0.0f);
        vs.push_back(z);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
      }
      for (float x=0.0f; x<=l; x++) {
        vs.push_back(x);
        vs.push_back(0.0f);
        vs.push_back(0.0f);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
        vs.push_back(x);
        vs.push_back(0.0f);
        vs.push_back(n);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
        vs.push_back(0.4f);
      }
      std::tie(vao,vbo) = partition(vs, 2, 3, 3);
    }

    void draw()
    {
      shader.use();
      glBindVertexArray(vao);
      // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glDrawArrays(GL_LINES, 0, 4*(l+m+n)+12);
    }

    // void draw_guide(glm::vec3 pos)
    // {
    //   // shader.use();
    //   // shader.setMat4("model", model);

    //   std::vector<float> guide_vs(36, 0.0f);
    //   guide_vs[0]  = pos.x;
    //   guide_vs[1]  = pos.y;
    //   guide_vs[2]  = pos.z;
    //   guide_vs[3]  = 1.0f;
    //   guide_vs[4]  = 0.0f;
    //   guide_vs[5]  = 0.0f;
    //   guide_vs[6]  = 0.0f;
    //   guide_vs[7]  = pos.y;
    //   guide_vs[8]  = pos.z;
    //   guide_vs[9]  = 1.0f;
    //   guide_vs[10] = 0.0f;
    //   guide_vs[11] = 0.0f;

    //   guide_vs[12] = pos.x;
    //   guide_vs[13] = pos.y;
    //   guide_vs[14] = pos.z;
    //   guide_vs[15] = 0.0f;
    //   guide_vs[16] = 1.0f;
    //   guide_vs[17] = 0.0f;
    //   guide_vs[18] = pos.x;
    //   guide_vs[19] = 0.0f;
    //   guide_vs[20] = pos.z;
    //   guide_vs[21] = 0.0f;
    //   guide_vs[22] = 1.0f;
    //   guide_vs[23] = 0.0f;

    //   guide_vs[24] = pos.x;
    //   guide_vs[25] = pos.y;
    //   guide_vs[26] = pos.z;
    //   guide_vs[27] = 0.0f;
    //   guide_vs[28] = 0.0f;
    //   guide_vs[29] = 1.0f;
    //   guide_vs[30] = pos.x;
    //   guide_vs[31] = pos.y;
    //   guide_vs[32] = 0.0f;
    //   guide_vs[33] = 0.0f;
    //   guide_vs[34] = 0.0f;
    //   guide_vs[35] = 1.0f;

    //   glBindBuffer(GL_ARRAY_BUFFER, guide_vbo);
    //   glBufferSubData(GL_ARRAY_BUFFER, 0, guide_vs.size()*sizeof(float), &guide_vs[0]);

    //   glBindVertexArray(guide_vao);
    //   glDrawArrays(GL_LINES, 0, 18);
    // }
  };

  class GridA
  {
  private:
    Shader shader;
    gle::Tetragon tetra;
  public:
    GridA(Shader shader = Shader3dColor()) : shader(shader), tetra(gle::Tetragon("resources/coord_tex.png"))
    {
      shader.setInt("texture0", tetra.texture);
    }

    void draw()
    {
      tetra.model = glm::mat4(1.0f);
      tetra.translate({0.5, 0.5, 0.0});
      for (int x=0; x<10; x++)
      {
        for (int y=0; y<10; y++)
        {
          shader.setMat4("model", tetra.model);
          tetra.draw();
          tetra.translate({0.0, 1.0, 0.0});
        }
        tetra.translate({1.0, -10.0, 0.0});
      }

      tetra.model = glm::mat4(1.0f);
      tetra.translate({0.5, 0.0, 0.5});
      tetra.rotate(90.0f, {1.0, 0.0, 0.0});
      for (int x=0; x<10; x++)
      {
        for (int z=0; z<10; z++)
        {
          shader.setMat4("model", tetra.model);
          tetra.draw();
          tetra.translate({0.0, 1.0, 0.0});
        }
        tetra.translate({1.0, -10.0, 0.0});
      }

      tetra.model = glm::mat4(1.0f);
      tetra.translate({0.0, 0.5, 0.5});
      tetra.rotate(90.0f, {0.0, 1.0, 0.0});
      for (int x=0; x<10; x++)
      {
        for (int y=0; y<10; y++)
        {
          shader.setMat4("model", tetra.model);
          tetra.draw();
          tetra.translate({0.0, 1.0, 0.0});
        }
        tetra.translate({-1.0, -10.0, 0.0});
      }
    }
  };
}

#endif