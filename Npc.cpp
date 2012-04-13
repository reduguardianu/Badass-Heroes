#include "Npc.h"
#include "ContainerRenderBehaviour.h"
#include "ContainerSizeBehaviour.h"
#include "AnimatedSprite.h"


Npc::Npc(Context const& c): DisplayObject(c) {
  DisplayObject* sprite = new AnimatedSprite(c, "zombie");
  sprite->setParent(this);

  m_sprites.push_back(sprite);
  
  m_render_behaviour = new ContainerRenderBehaviour(m_sprites);
  m_size_behaviour = new ContainerSizeBehaviour(m_sprites);

}

void Npc::animate(const std::string& dir) {
  for (int i = 0; i < m_sprites.size(); ++i) {
    dynamic_cast<AnimatedSprite*>(m_sprites.at(i))->animate(dir);
  }

}

void Npc::stop() {
  for (int i = 0; i < m_sprites.size(); ++i) {
    dynamic_cast<AnimatedSprite*>(m_sprites.at(i))->animate(Animations::idle);
  }
}

void Npc::tick(float dt) {
  
}
