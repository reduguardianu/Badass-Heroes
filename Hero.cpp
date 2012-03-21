#include "Hero.h"
#include "AnimatedSprite.h"
#include "ContainerRenderBehaviour.h"
#include "ContainerSizeBehaviour.h"

Hero::Hero(Context const& c): DisplayObject(c) {
  m_sprites.push_back(new AnimatedSprite(c, "base_walking.png"));
  m_sprites.push_back(new AnimatedSprite(c, "tights_01.png"));
  m_sprites.push_back(new AnimatedSprite(c, "breastplate_01.png"));
  m_sprites.push_back(new AnimatedSprite(c, "headgear_01.png"));

  for (int i = 0; i < m_sprites.size(); ++i) {
    m_sprites.at(i)->setParent(this);
  }

  m_render_behaviour = new ContainerRenderBehaviour(m_sprites);
  m_size_behaviour = new ContainerSizeBehaviour(m_sprites);
}


void Hero::animate(Anim::DIRECTION dir) {
  for (int i = 0; i < m_sprites.size(); ++i) {
    dynamic_cast<AnimatedSprite*>(m_sprites.at(i))->animate(dir);
  }
}

void Hero::stop() {
  for (int i = 0; i < m_sprites.size(); ++i) {
    dynamic_cast<AnimatedSprite*>(m_sprites.at(i))->stop();
  }
  
}

Hero::~Hero() {
  for (int i = 0; i < m_sprites.size(); ++i) {
    delete m_sprites.at(i);
  }

}
