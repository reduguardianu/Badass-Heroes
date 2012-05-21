#include "Npc.h"
#include "ContainerRenderBehaviour.h"
#include "ContainerSizeBehaviour.h"
#include "AnimatedSprite.h"
#include <iostream>
#include <cmath>
#include "Utils.h"

Npc::Npc(Context const& c, int health, std::vector<std::vector<int> > const& map): Character(c, health, map) {
  DisplayObject* sprite = new AnimatedSprite(c, "zombie");
  addChild(sprite);
  
  m_render_behaviour = new ContainerRenderBehaviour(m_children);
  m_size_behaviour = new ContainerSizeBehaviour(m_children);



  for (int i = 0; i < m_map.size(); ++i) {
    m_seen.push_back(std::vector<bool>());
    for (int j = 0; j < m_map.at(i).size(); ++j) {
      m_seen.at(i).push_back(true);
    }
  }

}

void Npc::animate(const std::string& dir, int count) {  
  for (int i = 0; i < m_children.size(); ++i) {
    AnimatedSprite* sprite = dynamic_cast<AnimatedSprite*>(m_children.at(i));
    if (sprite) {
      sprite->animate(dir, count);
    }
  }

}

void Npc::stop() {
  animate(Animations::idle);
  /*  for (int i = 0; i < m_sprites.size(); ++i) {
    dynamic_cast<AnimatedSprite*>(m_sprites.at(i))->stop();
    }*/
}

void Npc::die() {
  animate(Animations::dead, 1);
  m_children.at(0)->addEventListener("animationfinish", this, static_cast<Listener>(&Npc::onDeath));
}

void Npc::onDeath(GameEventPointer e, EventDispatcher* dispatcher) {
  if (parent()) {
    parent()->removeChild(this);
  }
}


void Npc::tick(float dt) {
  Character::tick(dt);

  for (int i = 0; i < m_children.size(); ++i) {
    m_children.at(i)->tick(dt);
  }

}
