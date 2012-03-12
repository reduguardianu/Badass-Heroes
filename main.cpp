#include "include/GL/glfw.h"
#include <iostream>
#include "StandardLogger.h"
#include "Game.h"

// need to define argc and argv or the linker complains on Windows
int main(int argc, char* argv[]) {
    int width = 800;
    int height = 600;


    Context context;
    Game game(width, height, context);

    double ms = context.timer->getMs();
    while (game.isRunning()) {
      double t = context.timer->getMs();      
      game.tick(t - ms);
      ms = t;
    }


    return 0;
}
