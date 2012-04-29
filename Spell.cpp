#include "Spell.h"
#include "Utils.h"
#include <cmath>
#include <iostream>

#define PI 3.14159265

Spell::Spell(Context const& c, std::string textureName):AnimatedSprite(c, textureName) {
}

void Spell::cast(std::pair<int, int> from, std::pair<int, int> to) {
  m_x = from.first * m_context.TILE_SIZE;
  m_y = from.second * m_context.TILE_SIZE;

  m_from = from;
  m_to = to;
  setRotation(-90.f);
  animate(Animations::idle);
}
 
void Spell::tick(float dt) {  
  point diff = Utils::getPositionDiff(point(m_x, m_y), point(m_to.first * m_context.TILE_SIZE, m_to.second * m_context.TILE_SIZE), dt);  
  setRotation(atan2(diff.second, diff.first) * 180 / PI - 90);
  m_x += diff.first;
  m_y += diff.second;  
  if (m_parent && m_x == m_to.first * m_context.TILE_SIZE && m_y == m_to.second * m_context.TILE_SIZE) {    
    dispatchEvent(ET::action, this);
  }
}
