#include "Level.h"
#include <cstdio>

Level::Level(Context const& c):m_width(0), m_height(0), m_context(c) {
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
      m_children.push_back(sprite);
    }
  }
}

void Level::tick(float dt) {
}

void Level::render() {
  for (unsigned int i = 0; i < m_children.size(); ++i) {
    m_children.at(i)->render();
  }
}

Level::~Level() {
  for (unsigned int i = 0; i < m_children.size(); ++i) {
    delete m_children.at(i);
  }
}
