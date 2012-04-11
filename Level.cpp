#include "Level.h"
#include <cstdio>
#include <iostream>
#include "ContainerRenderBehaviour.h"
#include "ContainerSizeBehaviour.h"
#include <cmath>

Level::Level(Context const& c): DisplayObject(c),
				m_camera_moved(false) {
  m_keys[Keyboard::Up] = false;
  m_keys[Keyboard::Right] = false;
  m_keys[Keyboard::Down] = false;
  m_keys[Keyboard::Left] = false;

  m_render_behaviour = new ContainerRenderBehaviour(m_children);
  m_size_behaviour = new ContainerSizeBehaviour(m_children);
}

void Level::loadFromFile(std::string filename) {
  FILE *file = NULL;
  
  file = fopen(filename.c_str(), "r");
  
  fscanf(file, "%d", &m_level_width);
  m_level_height = m_level_width;

  for (int i = 0; i < m_level_height; ++i) {
    m_data.push_back(std::vector<int>());
    for (int j = 0; j < m_level_width; ++j) {
      int block = 0;
      fscanf(file, "%d", &block);
      m_data.at(i).push_back(block);
    }
    fscanf(file, "\n");
  }

  fclose(file);
  
  initData();

}

void Level::initData() {  
  
  Sprite* floor = new Sprite(m_context, "floor.png");
  floor->setSize(m_level_width * m_context.TILE_SIZE, m_level_height * m_context.TILE_SIZE);
  floor->setScale(m_context.DEFAULT_SCALE);
  addChild(floor);

  for (unsigned int i = 0; i < m_data.size(); ++i) {
    for (unsigned int j = 0; j < m_data.at(i).size(); ++j) {
      Tile* tile = new Tile(m_context, "tileset.png", "tileset2-shadows.png", i, j, m_data);      
      tile->setScale(m_context.DEFAULT_SCALE);
      tile->setPosition(j * tile->width() * tile->scaleX(), i * tile->height() * tile->scaleY());
      addChild(tile);
      m_tiles.push_back(tile);
    }
  }

}

std::vector<std::vector<int> > const& Level::getData() {
  return m_data;
}

void Level::addChild(DisplayObject* child) {
  child->setParent(this);
  m_children.push_back(child);
}

void Level::tick(float dt) {  
  float dx = 0;
  float dy = 0;
  float diff = dt / 1000.0f * 512.0f;
  if (m_keys.at(Keyboard::Right)) {
    dx -= diff;
  }
  if (m_keys.at(Keyboard::Left)) {
    dx += diff;
  }
  if (m_keys.at(Keyboard::Down)) {
    dy -= diff;
  }
  if (m_keys.at(Keyboard::Up)) {
    dy += diff;
  }

  if (m_x + dx <= 0 && m_x + dx >= m_context.screen_width - m_level_width * m_context.TILE_SIZE) {
    m_x += dx;
  }
  if (m_y + dy <= 0 && m_y + dy >= m_context.screen_height - m_level_height * m_context.TILE_SIZE) {
    m_y += dy;
  }

  for (int i = 0; i < m_tiles.size(); ++i) {
    int row = m_tiles.at(i)->row();
    int col = m_tiles.at(i)->column();
    bool visible = m_hero->isTileVisible(row, col);    
    m_tiles.at(i)->setVisible(visible);
    //    m_tiles.at(i)->setDarknessOffset(m_hero->getTileOffset());
    m_tiles.at(i)->tick(dt);
  }


  if (m_hero->isMoving() && !m_camera_moved) {
    moveCamera(dt);
  }
  else if (!m_hero->isMoving()) {
    m_camera_moved = false;
  }

}

void Level::setCurrentPlayer(Hero* hero) {
  m_hero = hero;
}

void Level::moveCamera(float dt) {
  

  float dx = -(m_hero->x() - m_context.screen_width / 2) / 2 ;
  if (fabs(dx) > 3) {
    dx *= (dt / 200.0f);
  }

  float x = m_x + dx;
  if (x <= 0 && x >= m_context.screen_width - m_level_width * m_context.TILE_SIZE) {
    m_x = x;
  }
  else if ( x > 0) {
    m_x = 0;
  }
  else {
    m_x = m_context.screen_width - m_level_width * m_context.TILE_SIZE;
  }

  float dy = -(m_hero->y() - m_context.screen_height / 2) / 2;
  if (fabs(dy) > 3) {
    dy *= dt / 200.0f;
  }
  float y = m_y + dy ;
  if (y <= 0 && y >= m_context.screen_height - m_level_height * m_context.TILE_SIZE) {
    m_y = y;
  }
  else if (y > 0) {
    m_y = 0;
  }
  else {
    m_y = m_context.screen_height - m_level_height * m_context.TILE_SIZE;
  }
}



void Level::onEvent(const Event& e) {
  if (e.event_type == EventType::KeyDown || e.event_type == EventType::KeyUp)  {
    Keyboard::KEY key = static_cast<Keyboard::KEY>(e.key_data.key);
    if (m_keys.find(key) != m_keys.end()) {
      m_keys[static_cast<Keyboard::KEY>(e.key_data.key)] = e.key_data.pressed_down;
      m_camera_moved = true;
    }
  }
}

Level::~Level() {
  for (unsigned int i = 0; i < m_children.size(); ++i) {
    delete m_children.at(i);
  }
}
