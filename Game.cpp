#include "Game.h"
#include "include/GL/glfw.h"
#include "IRenderer.h"
#include "ILogger.h"
#include "Types.h"
#include <iostream>

Game::Game(Context& c, char* mapfile): m_context(c),
				       m_level(m_context),
				       m_hud(m_context),
				       m_running(false),
				       m_elapsed_time(0.0f), 
				       FRAME_RATE(32.0f),
				       FRAME_TIME(1000.f / 32.0f),
				       m_zombie(NULL) {
  
  m_hud.setPosition(m_context.screen_width - 250, 0);

  m_level.loadFromFile(mapfile);
  m_level.spawnNpcs(50);




  Hero* hero1 = new Hero(m_context, m_level.getData(), "headgear_01", "breastplate_01", "tights_01");
  hero1->setPosition(32.0f * m_context.DEFAULT_SCALE, 32.0f * m_context.DEFAULT_SCALE);
  hero1->setScale(m_context.DEFAULT_SCALE);
  hero1->animate(Animations::down);
  m_level.addChild(hero1);
  m_heroes.push_back(hero1);

  Hero* hero2 = new Hero(m_context, m_level.getData(), "headgear_02", "breastplate_02", "tights_02");
  hero2->setPosition(2 * m_context.TILE_SIZE, m_context.TILE_SIZE);
  hero2->setScale(m_context.DEFAULT_SCALE);
  hero2->animate(Animations::down);
  m_level.addChild(hero2);
  m_heroes.push_back(hero2);



  m_level.setCurrentPlayer(hero1);
  m_hud.setAvatar(hero1->getAvatar());


  m_context.renderer->setSize(m_context.screen_width, m_context.screen_height);
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
  if (e.event_type == EventType::Resize) {
    m_context.screen_width = e.resize_data.width;
    m_context.screen_height = e.resize_data.height;
    m_context.renderer->setSize(m_context.screen_width, m_context.screen_height);
  }
  else if (e.event_type == EventType::KeyDown) {
    if (e.key_data.key == '1') {
      m_level.setCurrentPlayer(m_heroes.at(0));
      m_hud.setAvatar(m_heroes.at(0)->getAvatar());
    }
    else if (e.key_data.key == '2') {
      m_level.setCurrentPlayer(m_heroes.at(1));
      m_hud.setAvatar(m_heroes.at(1)->getAvatar());
    }
  }
  
  m_level.onEvent(e);
  m_hud.onEvent(e);
}

void Game::tick(float dt) {

  m_level.tick(dt);
  m_elapsed_time += dt;
  if (m_elapsed_time >= FRAME_TIME) {

    m_context.renderer->beginFrame();
    m_level.render();
    m_hud.render();
    m_context.renderer->renderText("badass heroes", "arial", 560, 250);
    m_context.renderer->renderText("finger unicorns", "arial", 560, 282);
    m_context.renderer->endFrame();
    m_elapsed_time -= FRAME_TIME;
  }

  m_running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
}

bool Game::isRunning() {
  return m_running;
}
