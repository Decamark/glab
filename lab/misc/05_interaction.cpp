/**
 * (Misc) 05: Interaction
 */

#include <glab/glab.hpp>
#include <glab/shape.hpp>
#include <glab/grid.hpp>
#include <glab/time.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/norm.hpp>

#include <learnopengl/camera.h>

const float PI = glm::pi<float>();
glm::vec3 ray = glm::vec3(0.0f);
// We cannot use glad-related APIs before calling initWindow, so just declare a pointer here
glab::Cube* cube;
glm::vec3 axis = {1.0f, 1.0f, 1.0f};
float theta = 0.0f;
glm::vec3 Front = {0.0f, 0.0f, 1.0f}, Right = {1.0f, 0.0f, 0.0f}, Up = {0.0f, 1.0f, 0.0f};

// Convert a coordinate in screen space to the one in eye space
std::pair<double,double> screen2eye(double xpos, double ypos)
{
  // The height and the width of the near plane
  float nh = 2 * 0.1 * glm::tan(glm::radians(45.0f/2));
  float nw = 1200.0f/800.0f * nh;

  float xe = (xpos - 1200/2) * nw/1200.0f;
  float ye = (800/2 - ypos) * nh/800.0f;
  return {xe, ye};
}

// Gets called whenever the cursor moves
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
  // Joey calculates yaw and pitch in the "screen space" to implement Camera.
  // ref: https://learnopengl.com/Getting-started/Camera
  // This works fine if the cursor's position doesn't matter
  // but I wanted to judge the intersection between an object and the cursor
  // and with Joey's method, it looks weird because the point of the ray vector
  // isn't covered with the cursor!
  // So, I needed to handle the cursor as if it's in the "eye space" to make it look more natural.
  auto [xe,ye] = screen2eye(xpos, ypos);
  ray = {xe, ye, -0.1f};

  static int shouldMove = false;
  static float lastX, lastY;

  if (shouldMove)
  {
    glm::vec3 l = Right * (float) (xe-lastX) + Up * (float) (ye-lastY);
    axis = glm::normalize(glm::cross(l, Front));
    float distance = glm::l2Norm(glm::vec3(cube->model[0][3], cube->model[1][3], cube->model[2][3])-(*camera).Position);
    theta = -glm::degrees( glm::atan(glm::l2Norm(l) * distance / 0.1f) );
  }

  int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  if (state == GLFW_PRESS and cube->intersect((*camera).Position, ray))
    shouldMove = true;
  else
    shouldMove = false;

  lastX = xe;
  lastY = ye;
}

int main()
{
  glab::initWindow(1200, 800, "glab", false, false, true, true);
  glfwSetCursorPosCallback(window, cursor_position_callback);

  Camera camera0 = Camera(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 100.0f);
  camera0 |= projection;
  camera  |= camera0;

  cube = new glab::Cube(0.0f, 0.0f, 0.0f, 5.0f);

  glab::clock.start();
  while (!glfwWindowShouldClose(window))
  {
    glab::clock.tick();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glab::Line beam((*camera).Position+glm::vec3(0.0f, 0.0f, -0.1f), {1.0f, 0.0f, 0.0f},
                    (*camera).Position+ray,                          {0.0f, 1.0f, 0.0f});
    beam.draw();

    Front = glm::rotate(Front, glm::radians(-theta), axis);
    Right = glm::rotate(Right, glm::radians(-theta), axis);
    Up    = glm::rotate(   Up, glm::radians(-theta), axis);

    cube->rotate(theta, axis);

    // glab::Line front(glm::vec3(0.0f, 0.0f, 0.0f), {1.0f, 1.0f, 0.0f}, Front*5.0f, {1.0f, 1.0f, 0.0f}); // yellow
    glab::Cube front(Front.x*3, Front.y*3, Front.z*3, 1.0f, {1.0f, 1.0f, 0.0f});
    // glab::Line right(glm::vec3(0.0f, 0.0f, 0.0f), {0.0f, 1.0f, 1.0f}, Right*5.0f, {0.0f, 1.0f, 1.0f}); // cyan
    glab::Cube right(Right.x*3, Right.y*3, Right.z*3, 1.0f, {0.0f, 1.0f, 1.0f});
    // glab::Line    up(glm::vec3(0.0f, 0.0f, 0.0f), {1.0f, 0.0f, 1.0f},    Up*5.0f, {1.0f, 0.0f, 1.0f}); // magenta
    glab::Cube up(Up.x*3, Up.y*3, Up.z*3, 1.0f, {1.0f, 0.0f, 1.0f});
    front.draw();
    right.draw();
       up.draw();

    if (cube->intersect((*camera).Position, ray))
      cube->rasterization = GL_FILL;
    else
      cube->rasterization = GL_LINE;
    cube->draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
    glab::getKeyWASD();
  }
}
