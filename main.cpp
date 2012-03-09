#include <GL/glfw.h>
#include <iostream>
#include "Renderer.h"
#include "Sprite.h"

int main(void) {
    int width = 800;
    int height = 600;

    if (glfwInit() == GL_FALSE) {
        std::cerr << "GLFW inititalization failed. Exiting... " << std::endl;
        return 1;
    }

    if (glfwOpenWindow(width, height, 8, 8, 8, 8, 24, 8, GLFW_WINDOW) == GL_FALSE) {
        std::cerr << "GLFW failed to open window. Exiting..." << std::endl;
        glfwTerminate();
        return 2;
    }

    Renderer renderer(width, height);
    Sprite sprite(renderer, "Ground.png");
    sprite.render();

    glfwSwapBuffers();

    sleep(10);

    glfwCloseWindow();
    glfwTerminate();
    return 0;
}
