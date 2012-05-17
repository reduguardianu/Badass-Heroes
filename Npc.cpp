#include "Npc.h"
#include "ContainerRenderBehaviour.h"
#include "ContainerSizeBehaviour.h"
#include "AnimatedSprite.h"
#include <iostream>


Npc::Npc(Context const& c): DisplayObject(c) {
  DisplayObject* sprite = new AnimatedSprite(c, "zombie");
  sprite->setParent(this);

  m_sprites.push_back(sprite);
  
  m_render_behaviour = new ContainerRenderBehaviour(m_sprites);
  m_size_behaviour = new ContainerSizeBehaviour(m_sprites);

}

void Npc::animate(const std::string& dir, int count) {
  for (int i = 0; i < m_sprites.size(); ++i) {
    dynamic_cast<AnimatedSprite*>(m_sprites.at(i))->animate(dir, count);
  }

}

void Npc::stop() {
  for (int i = 0; i < m_sprites.size(); ++i) {
    dynamic_cast<AnimatedSprite*>(m_sprites.at(i))->stop();
  }
}

void Npc::die() {
  animate(Animations::dead, 1);
  m_sprites.at(0)->addEventListener("animationfinish", this, static_cast<Listener>(&Npc::onDeath));
}

void Npc::onDeath(GameEvent e, EventDispatcher* dispatcher) {
  if (parent()) {
    parent()->removeChild(this);
  }
}

void Npc::tick(float dt) {
  for (int i = 0; i < m_sprites.size(); ++i) {
    m_sprites.at(i)->tick(dt);
  }

}
