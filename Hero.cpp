#include "Hero.h"

Hero::Hero(Context const& c): AnimatedSprite(c, "") {
  m_sprites.push_back(new AnimatedSprite(c, "base_walking.png"));
  m_sprites.push_back(new AnimatedSprite(c, "tights_01.png"));
  m_sprites.push_back(new AnimatedSprite(c, "breastplate_01.png"));
  m_sprites.push_back(new AnimatedSprite(c, "headgear_01.png"));

  for (int i = 0; i < m_sprites.size(); ++i) {
    m_sprites.at(i)->setParent(this);
  }
}

void Hero::render() {
  for (int i = 0; i < m_sprites.size(); ++i) {
    m_sprites.at(i)->render();
  } 
}

void Hero::animate(Anim::DIRECTION dir) {
  for (int i = 0; i < m_sprites.size(); ++i) {
    m_sprites.at(i)->animate(dir);
  }
}

void Hero::stop() {
  for (int i = 0; i < m_sprites.size(); ++i) {
    m_sprites.at(i)->stop();
  }
  
}

Hero::~Hero() {
  for (int i = 0; i < m_sprites.size(); ++i) {
    delete m_sprites.at(i);
  }

}
