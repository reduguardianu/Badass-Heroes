#include "include/GL/glfw.h"
#include <iostream>
#include "ILogger.h"
#include "StandardLogger.h"
#include "Renderer.h"
#include "Sprite.h"

// need to define argc and argv or the linker complains on Windows
int main(int argc, char* argv[]) {
    int width = 800;
    int height = 600;

    ILogger* logger = new StandardLogger();

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
    // not cross-platform function
    //    sleep(10);

    delete logger;
    glfwCloseWindow();
    glfwTerminate();
    return 0;
}
