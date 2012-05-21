#include "include/GL/glfw.h"
#include <iostream>
#include "StandardLogger.h"
#include "Game.h"
#include "Types.h"
#include "Event.h"
#include <cstdio>


Game* game;

int mouse_x;
int mouse_y;


void GLFWCALL handleKeypress(int glfw_key, int action) {
  
  Event e;
  if (action == GLFW_PRESS) {
    e.event_type = EventType::KeyDown;
    e.key_data.pressed_down = true;
  }
  else {
    e.event_type = EventType::KeyUp;
    e.key_data.pressed_down = false;
  }
  switch (glfw_key) {
  case GLFW_KEY_UP:
    e.key_data.key = Keyboard::Up;
    break;
  case GLFW_KEY_RIGHT:
    e.key_data.key = Keyboard::Right;
    break;
  case GLFW_KEY_DOWN:
    e.key_data.key = Keyboard::Down;
    break;
  case GLFW_KEY_LEFT:
    e.key_data.key = Keyboard::Left;
    break;
  default:
    e.key_data.key = glfw_key;
  }
  
  game->onEvent(e);
}

void GLFWCALL handleMousePosition(int x, int y) {
  mouse_x = x;
  mouse_y = y;
  
  Event e;
  e.event_type = EventType::MouseMoved;

  e.mouse_data.x = mouse_x;
  e.mouse_data.y = mouse_y;

  game->onEvent(e);
  
}

void GLFWCALL handleMousePress(int button, int action) {
  Event e;
  e.mouse_data.x = mouse_x;
  e.mouse_data.y = mouse_y;

  if (action == GLFW_PRESS) {
    e.event_type = EventType::MouseDown;
  }
  else if (action == GLFW_RELEASE) {
    e.event_type = EventType::MouseUp;
  }
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    e.mouse_data.button = MouseButton::Left;
  }
  else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
    e.mouse_data.button = MouseButton::Right;
  }
  else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
    e.mouse_data.button = MouseButton::Middle;
  }

  game->onEvent(e);
}

void GLFWCALL handleWindowResize(int width, int height) {
  Event e;
  e.event_type = EventType::Resize;

  e.resize_data.width = width;
  e.resize_data.height = height;

  game->onEvent(e);
}



// need to define argc and argv or the linker complains on Windows
int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "No map file specified, usage: ./BadassHeroes map.txt" << std::endl;
    return 1;
  }

  FILE* file = NULL;
  file = fopen(argv[1], "r");
  if (!file) {
    fclose(file);
    std::cout << "Cannot open file " << argv[1] << std::endl;
    return 1;
  }

   
  Context context;
  context.screen_width = 800;
  context.screen_height = 600;
  game = new Game(context, argv[1]);
  
  glfwSetKeyCallback(handleKeypress);
  glfwSetMousePosCallback(handleMousePosition);
  glfwSetMouseButtonCallback(handleMousePress);
  glfwSetWindowSizeCallback(handleWindowResize);
  

  double ms = context.timer->getMs();
  while (game->isRunning()) {
    double t = context.timer->getMs();      
    game->tick(t - ms);
    ms = t;
    glfwSleep(0.001);
  }

  return 0;
}
