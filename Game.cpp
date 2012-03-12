#include "Game.h"
#include "include/GL/glfw.h"
#include "IRenderer.h"
#include "ILogger.h"

Game::Game(int width, int height, Context const& c): m_context(c),
						     m_level(m_context),
						     m_running(false) {
  
  m_context.renderer->setSize(width, height);
  m_level.loadFromFile("map.txt");

  createWindow();

  m_running = true;
    
}

Game::~Game() {
  destroy();
}

void Game::destroy() {
  glfwCloseWindow();
  glfwTerminate();
}

void Game::createWindow() {
    if (glfwInit() == GL_FALSE) {
        m_context.logger->CriticalError("GLFW inititalization failed. Exiting... ");
	destroy();
        return;
    }
    else {
        m_context.logger->Debug("GLFW initialized. Now I will try to create window...");
    }

    if (glfwOpenWindow(m_context.renderer->getWindowWidth(), m_context.renderer->getWindowHeight(), 8, 8, 8, 8, 24, 8, GLFW_WINDOW) == GL_FALSE) {
        m_context.logger->CriticalError("GLFW failed to open window. Exiting...");
	destroy();
        return;
    }
    else {
        m_context.logger->Debug("Window creation successfull");
    }

}

void Game::tick(float dt) {
  m_level.tick(dt);

  //TODO: game should create context, so we can remove beginFrame and endFrame from IRenderer, so only game knows about it
  m_context.renderer->beginFrame();
  m_level.render();
  m_context.renderer->endFrame();

  m_running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
}

bool Game::isRunning() {
  return m_running;
}
