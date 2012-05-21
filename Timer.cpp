#include "Timer.h"
#include "include/GL/glfw.h"

double Timer::getMs() {
  return glfwGetTime() * 1000.0;
}
