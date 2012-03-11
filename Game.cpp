#include "Game.h"
#include "include/GL/glfw.h"

Game::Game(Context const& c):m_context(c),
			     m_level(m_context),
			     m_running(true) {
    m_level.loadFromFile("map.txt");

}

void Game::tick(float dt) {
  m_level.tick(dt);

  //TODO: game should create context, so we can remove beginFrame and endFrame from IRenderer, so only game knows about it
  m_context.m_renderer->beginFrame();
  m_level.render();
  m_context.m_renderer->endFrame();

  m_running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
}

bool Game::isRunning() {
  return m_running;
}
