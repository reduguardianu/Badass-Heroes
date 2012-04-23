#ifndef SPELL_H__
#define SPELL_H__

#include "AnimatedSprite.h"

class Spell : public AnimatedSprite {
 public:
  explicit Spell(Context const& c, std::string textureName);
  void cast(std::pair<int, int> from, std::pair<int, int> to);
  void tick(float dt);
  //  void stop();
 private:
  std::pair<int, int> m_from;
  std::pair<int, int> m_to;
};

#endif
