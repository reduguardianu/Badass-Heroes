#include "Level.h"
#include <cstdio>
#include <iostream>

Level::Level(Context const& c):m_width(0), m_height(0), m_context(c) {
  m_keys[Keyboard::Up] = false;
  m_keys[Keyboard::Right] = false;
  m_keys[Keyboard::Down] = false;
  m_keys[Keyboard::Left] = false;
}

void Level::loadFromFile(std::string filename) {
  FILE *file = NULL;
  
  file = fopen(filename.c_str(), "r");
  
  fscanf(file, "%d", &m_width);
  m_height = m_width;

  for (int i = 0; i < m_height; ++i) {
    m_data.push_back(std::vector<int>());
    for (int j = 0; j < m_width; ++j) {
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
  for (unsigned int i = 0; i < m_data.size(); ++i) {
    for (unsigned int j = 0; j < m_data.at(i).size(); ++j) {
      std::string texture;
      if (m_data.at(i).at(j) == 0) {
	texture = "Ground.png";
      }
      else {
	texture = "Wall.png";
      }
      Sprite* sprite = new Sprite(m_context, texture);
      //TODO: sprite must know its width and height, so sprite class has to load image, not renderer
      sprite->setScale(32.0f/20.0f, 32.0f/20.0f);
      sprite->setPosition(i * 32, j * 32);
      addChild(sprite);
    }
  }
}

void Level::addChild(IDrawable* child) {
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

  if (m_x + dx <= 0 && m_x + dx >= m_context.screen_width - m_width * 32.0f) {
    m_x += dx;
  }
  if (m_y + dy <= 0 && m_y + dy >= m_context.screen_height - m_height * 32.0f) {
    m_y += dy;
  }

}

int Level::x() const {
  return static_cast<int>(m_x);
}

int Level::y() const {
  return static_cast<int>(m_y);
}

float Level::scaleX() const {
  return m_scale_x;
}

float Level::scaleY() const {
  return m_scale_y;
}

const char* Level::texture() const {
  return NULL;
}

void Level::setParent(const IDrawable* parent) {
  m_parent = parent;
}

void Level::render() {
  for (unsigned int i = 0; i < m_children.size(); ++i) {
    m_children.at(i)->render();
  }
}

void Level::onEvent(const Event& e) {
  if (e.event_type == EventType::KeyDown || e.event_type == EventType::KeyUp)  {
    Keyboard::KEY key = static_cast<Keyboard::KEY>(e.key_data.key);
    if (m_keys.find(key) != m_keys.end()) {
      m_keys[static_cast<Keyboard::KEY>(e.key_data.key)] = e.key_data.pressed_down;
    }
  }
}

Level::~Level() {
  for (unsigned int i = 0; i < m_children.size(); ++i) {
    delete m_children.at(i);
  }
}
