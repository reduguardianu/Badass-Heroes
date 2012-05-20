#include "Game.h"
#include "include/GL/glfw.h"
#include "IRenderer.h"
#include "ILogger.h"
#include "Types.h"
#include <iostream>
#include "Utils.h"
#include <time.h>
#include <cstdlib>
#include <sstream>
#include "BuildSpell.h"

Game::Game(Context& c, char* mapfile): m_context(c),
				       m_level(m_context),
				       m_hud(m_context),
				       m_running(false),
				       m_elapsed_time(0.0f), 
				       FRAME_RATE(32.0f),
				       FRAME_TIME(1000.f / FRAME_RATE),
				       m_end_turn(NULL),
				       m_current_player(0),
				       m_spell(NULL),
				       m_fps_text("0"),
				       m_fps_counter(0),
				       m_fps_time(0.f) {
  
  srand(time(NULL));
  m_hud.setPosition(m_context.screen_width - 250, 0);
  m_end_turn = new Button(m_context, "inactive.png", "active.png", "inactive.png", "End turn");
  m_end_turn->setPosition(10, 500);
  m_end_turn->setParent(&m_hud);
  m_end_turn->setZ(1.0f);

  m_spell = new Button(m_context, "spell1.png", "spell1.png", "spell2.png", "");
  m_spell->setPosition(10, 350);
  m_spell->setParent(&m_hud);
  m_spell->setZ(1.0f);

  m_build_spell = new Button(m_context, "buildspell1.png", "buildspell1.png", "buildspell2.png", "");
  m_build_spell->setPosition(74, 350);
  m_build_spell->setParent(&m_hud);
  m_build_spell->setZ(1.0f);

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
  //  m_heroes.push_back(hero2);


  m_level.setPlayers(&m_heroes);
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
      glfwSetWindowTitle("Badass Heroes: Ninja Pirate Robot Cowboy Space Wizards from Space");
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

  if (e.event_type == EventType::MouseMoved) {
    m_context.uistate.mousex = e.mouse_data.x;
    m_context.uistate.mousey = e.mouse_data.y;
  }
  else if (e.event_type == EventType::MouseDown) {
    if (e.mouse_data.button == MouseButton::Left) {
      m_context.uistate.mousedown = 1;
    }
  }
  else if (e.event_type == EventType::MouseUp) {
    if (e.mouse_data.button == MouseButton::Left) {
      m_context.uistate.mousedown = 0;
    }
  }
   
  
  if (e.event_type == EventType::MouseMoved || e.event_type == EventType::MouseUp || e.event_type == EventType::MouseDown) {
    if (Utils::rectHit(e.mouse_data.x, e.mouse_data.y, m_level.bounds())) {
      m_level.onEvent(e);
    }
    else {
      m_hud.onEvent(e);
    }
  }
  else {
    m_level.onEvent(e);
    m_hud.onEvent(e);
  }
}

void Game::tick(float dt) {

  m_level.tick(dt);
  m_elapsed_time += dt;    
  countFPS(dt);    

  if (m_elapsed_time >= FRAME_TIME) {
    m_fps_counter++;
    m_context.renderer->beginFrame();
    m_level.render();
    m_hud.render();
    doGUI();
    m_context.renderer->renderText(m_fps_text, "Arial", 0, 0);
    m_context.renderer->endFrame();
    m_elapsed_time -= FRAME_TIME;
  }

  m_running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
}

void Game::countFPS(float dt) {
  m_fps_time += dt;
  if (m_fps_time >= 1000) {
    std::ostringstream txt;
    txt << m_fps_counter;
    m_fps_text = txt.str();
    m_fps_time -= 1000;
    m_fps_counter = 0;
  }

}

bool Game::isRunning() {
  return m_running;
}

void Game::endTurn() {  
  if (m_current_player == m_heroes.size() - 1) {
    m_level.npcTurn();
    m_level.addEventListener(ET::npc_turn_ended, this, static_cast<Listener>(&Game::onNpcTurnEnd));
  }
  else {
    m_current_player = (m_current_player + 1) % m_heroes.size();
    m_level.setCurrentPlayer(m_heroes.at(m_current_player));
    m_hud.setAvatar(m_heroes.at(m_current_player)->getAvatar());
  }
}

void Game::onNpcTurnEnd(GameEventPointer event, EventDispatcher* dispatcher) {
  m_current_player = 0;
  m_level.setCurrentPlayer(m_heroes.at(m_current_player));
  m_hud.setAvatar(m_heroes.at(m_current_player)->getAvatar());
}

bool Game::button(Button* b) {
  int id = reinterpret_cast<int>(b);
  if (Utils::regionHit(m_context.uistate.mousex, m_context.uistate.mousey, b)) {
    m_context.uistate.hot = id;
    if (m_context.uistate.active == 0 && m_context.uistate.mousedown) {
      m_context.uistate.active = id;
    }
  }

  if (m_context.uistate.active == id) {
    b->setPressed();
  }
  else if (m_context.uistate.last == id) {
    b->setSelected();
  }
  else {
    b->setNormal();
  }
    
  b->render();

  if (m_context.uistate.mousedown == 0 && m_context.uistate.hot == id && 
      m_context.uistate.active == id) {
    m_context.uistate.last = id;

    return true;
  }

  return false;
}

void Game::doGUI() {
  m_context.uistate.hot = 0;


  if (button(m_end_turn)) {
    endTurn();
  }

  if (button(m_build_spell)) {
    m_heroes.at(m_current_player)->spell(new BuildSpell(m_context));
  }


  if (button(m_spell)) {    
    m_heroes.at(m_current_player)->spell(new Spell(m_context, "magic-bullet") );
  }



  if (m_context.uistate.mousedown == 0) {
    m_context.uistate.active = 0;
  }
  else if (m_context.uistate.active == 0) {
    m_context.uistate.active = -1;
  }

  if (m_context.uistate.mousedown == 1 && m_context.uistate.last != 0) {
    m_context.uistate.last = 0;
  }
}

