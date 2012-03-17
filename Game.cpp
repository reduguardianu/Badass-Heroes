#include "Game.h"
#include "include/GL/glfw.h"
#include "IRenderer.h"
#include "ILogger.h"
#include "Types.h"

Game::Game(Context const& c): m_context(c),
						     m_level(m_context),
						     m_running(false),
						     m_elapsed_time(0.0f), 
						     FRAME_RATE(32.0f),
						     FRAME_TIME(1000.f / 32.0f),
						     m_hero(NULL) {
  
  m_context.renderer->setSize(m_context.screen_width, m_context.screen_height);
  m_level.loadFromFile("map.txt");

  m_hero = new AnimatedSprite(m_context, "hero.png");
  //  m_hero->setPosition(width/2 - 16, height/2 - 16);
  m_hero->setPosition(32.0f, 32.0f);
  m_hero->setScale(1.0f, 1.0f);
  m_hero->animate(Anim::Down);
  m_level.addChild(m_hero);

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
      glfwSetWindowTitle("Badass Heroes baby");
        m_context.logger->Debug("Window creation successfull");
    }

}

void Game::onEvent(const Event& e) {
  m_level.onEvent(e);
}

void Game::tick(float dt) {
  m_level.tick(dt);

  m_elapsed_time += dt;
  if (m_elapsed_time >= FRAME_TIME) {
    m_context.renderer->beginFrame();
    m_level.render();
    m_context.renderer->endFrame();
    m_elapsed_time -= FRAME_TIME;
  }

  m_running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
}

bool Game::isRunning() {
  return m_running;
}
