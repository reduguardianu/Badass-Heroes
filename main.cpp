#include "include/GL/glfw.h"
#include <iostream>
#include "StandardLogger.h"
#include "Renderer.h"
#include "Context.h"
#include "Game.h"

// need to define argc and argv or the linker complains on Windows
int main(int argc, char* argv[]) {
    int width = 800;
    int height = 600;

    ILogger* logger = new StandardLogger();
    IRenderer* renderer = new Renderer(width, height);
    Context c(renderer, logger);

    if (glfwInit() == GL_FALSE) {
        logger->CriticalError("GLFW inititalization failed. Exiting... ");
        delete logger;
        return 1;
    }
    else {
        logger->Debug("GLFW initialized. Now I will try to create window...");
    }

    if (glfwOpenWindow(width, height, 8, 8, 8, 8, 24, 8, GLFW_WINDOW) == GL_FALSE) {
        logger->CriticalError("GLFW failed to open window. Exiting...");
        delete logger;
        glfwTerminate();
        return 2;
    }
    else {
        logger->Debug("Window creation successfull");
    }

    Game game(c);
    double ms = glfwGetTime() * 1000;;
    while (game.isRunning()) {
      double t = glfwGetTime() * 1000;      
      game.tick(t - ms);
      ms = t;
    }


    delete logger;
    glfwCloseWindow();
    glfwTerminate();
    return 0;
}
