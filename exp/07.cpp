/**
 * 07: Time
 */

#include <functional>

#include <gle/gle.hpp>
#include <gle/export.hpp>
#include <gle/shape.hpp>
#include <gle/system.hpp>
#include <gle/time.hpp>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>

auto* window = gle::setup(800, 600, "Practice");
Camera camera(window, glm::vec3(25.0f, 25.0f, 25.0f), glm::vec3(0.0f, 1.0f, 0.0f), -135.0f, -45.0f);

int main()
{
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

  gle::Cartesian system(50);
  system.shader.use();
  system.shader.setMat4("projection", projection);

  gle::Cube cube;
  cube.translate({5.0f, 5.0f, 5.0f});
  cube.shader.use();
  cube.shader.setMat4("projection", projection);

  gle::Clock clock;
  while (!glfwWindowShouldClose(window))
  {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.processInput(clock.tick());
    std::cout << clock.t << std::endl;

    cube.shader.setMat4("view", camera.GetViewMatrix());
    std::function<void(double)> motion =
      [&cube](double t) {
        cube.translate({0.01f, glm::sin(t)*0.1, 0.01f});
      };
    cube.move(motion, clock.t);
    cube.draw();

    system.shader.setMat4("view", camera.GetViewMatrix());
    system.draw();
    system.draw_guide({cube.model[3][0], cube.model[3][1], cube.model[3][2]});

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}
