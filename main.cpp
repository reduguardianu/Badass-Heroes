#include "include/GL/glfw.h"
#include <iostream>
#include "StandardLogger.h"
#include "Game.h"
#include "Types.h"
#include "Event.h"
#include <cstdio>

Game* game;

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
  }
  
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


    double ms = context.timer->getMs();
    while (game->isRunning()) {
      double t = context.timer->getMs();      
      game->tick(t - ms);
      ms = t;
    }


    return 0;
}
