#include "Figure.h"
#include "ContainerRenderBehaviour.h"
#include "ContainerSizeBehaviour.h"


Figure::Figure(Context const& c, std::string headgear, std::string breastplate, std::string pants):DisplayObject(c) {

  init(headgear, breastplate, pants);
}

void Figure::init(std::string headgear, std::string breastplate, std::string pants) {
  m_sprites.push_back(new AnimatedSprite(m_context, "base"));
  m_sprites.push_back(new AnimatedSprite(m_context, pants));
  m_sprites.push_back(new AnimatedSprite(m_context, breastplate));
  m_sprites.push_back(new AnimatedSprite(m_context, headgear));

  for (int i = 0; i < m_sprites.size(); ++i) {
    addChild(m_sprites.at(i));
  }

  m_render_behaviour = new ContainerRenderBehaviour(m_children);
  m_size_behaviour = new ContainerSizeBehaviour(m_children);  

}

void Figure::setScale(float value) {
  for (int i = 0; i < m_sprites.size(); ++i) {
    m_sprites.at(i)->setScale(value);
  }
}

Figure::Figure(const Figure& f): DisplayObject(f.m_context) {
  std::string headgear = f.headgear();
  std::string breastplate = f.breastplate();
  std::string pants = f.pants();
  init(headgear, breastplate, pants);
}

std::string Figure::headgear() const {
  return m_sprites.at(1)->spritesheet();
}

std::string Figure::breastplate() const {
  return m_sprites.at(2)->spritesheet();
}

std::string Figure::pants() const {
  return m_sprites.at(3)->spritesheet();
}


void Figure::animate(std::string dir) {
  for (int i = 0; i < m_sprites.size(); ++i) {
    m_sprites.at(i)->animate(dir);
  }
}

void Figure::setDirection(std::string dir) {
  for (int i = 0; i < m_sprites.size(); ++i) {
    m_sprites.at(i)->setDirection(dir);
  }
}

void Figure::stop() {
  for (int i = 0; i < m_sprites.size(); ++i) {
    m_sprites.at(i)->stop();
    m_sprites.at(i)->setDirection(Animations::down);
  }
}

void Figure::gotoFrame(int frame, int time) {
  for (int i = 0; i < m_sprites.size(); ++i) {
    m_sprites.at(i)->gotoFrame(frame, time);
  }
}

void Figure::tick(float dt) {
  for (int i = 0; i < m_sprites.size(); ++i) {
    m_sprites.at(i)->tick(dt);
  }
}

Figure::~Figure() {
  for (int i = 0; i < m_sprites.size(); ++i) {
    if (m_sprites.at(i)) {
      delete m_sprites.at(i);
    }
  }
}
