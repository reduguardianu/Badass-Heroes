#include "Level.h"
#include <cstdio>
#include <iostream>
#include "ContainerRenderBehaviour.h"
#include "ContainerSizeBehaviour.h"
#include <cmath>
#include <cstdlib>
#include <time.h>
#include "Spell.h"

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
  floor->setZ(-1);
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

  for (unsigned int i = 0; i < m_data.size(); ++i) {
    for (unsigned int j = 0; j < m_data.at(i).size(); ++j) {
      std::vector<Tile*> neighbours;
      if (j > 0) {
	neighbours.push_back(m_tiles.at(j - 1 + i * m_data.at(i).size()));
      }
      if (j < m_data.at(i).size() - 1) {
	neighbours.push_back(m_tiles.at(j + 1 + i * m_data.at(i).size()));
      }
      if (i > 0) {
	neighbours.push_back(m_tiles.at(j + (i - 1) * m_data.at(i).size()));
      }
      if (i < m_data.size() - 1) {
	neighbours.push_back(m_tiles.at(j + (i + 1) * m_data.at(i).size()));
      }

      m_tiles.at(j + i * m_data.at(i).size())->setNeighbours(neighbours);
    }
  }

}

void Level::spawnNpcs(int count) {
  srand ( time(NULL) );
  std::set<std::pair<int, int> > marked;
  for (int i = 0; i < count; ++i) {
    Npc* npc = new Npc(m_context);
    
    int row = 0;
    int col = 0;
    do {
      row = rand() % m_data.size();
      col = rand() % m_data.at(0).size();
    } while (m_data.at(row).at(col) == 1 || marked.find(std::make_pair(row, col)) != marked.end());

    marked.insert(std::make_pair(row, col));
    npc->setPosition(m_context.TILE_SIZE * col, m_context.TILE_SIZE * row);
    npc->animate(Animations::idle);
    m_npcs.push_back(npc);
    addChild(npc);
  }
  
}

std::vector<std::vector<int> > const& Level::getData() {
  return m_data;
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
  }
  
  for (int i = 0; i < m_children.size(); ++i) {
    m_children.at(i)->tick(dt);
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
  m_hero->addEventListener(ET::action, this, static_cast<Listener>(&Level::onSpellCasted));
}

void Level::onSpellCasted(std::string e, EventDispatcher* dispatcher) {
  Spell* spell = dynamic_cast<Spell*>(dispatcher);

  for (int i = 0; i < m_npcs.size(); ++i) {
    if (m_npcs.at(i)->row() == spell->row() && m_npcs.at(i)->col() == spell->col()) {
      m_npcs.at(i)->die();
    }
  }

  for (int i = 0; i < m_tiles.size(); ++i) {
    if (m_tiles.at(i)->row() == spell->row() && m_tiles.at(i)->col() == spell->col()) {
      if (m_tiles.at(i)->parent()) {
	m_data.at(spell->row()).at(spell->col()) = 0;
      }
    }
  }
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

  m_hero->onEvent(e);
}

Level::~Level() {
  for (unsigned int i = 0; i < m_children.size(); ++i) {
    delete m_children.at(i);
  }
}
