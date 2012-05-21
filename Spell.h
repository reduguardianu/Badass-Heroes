#ifndef SPELL_H__
#define SPELL_H__

#include "AnimatedSprite.h"
#include "Event.h"

class Spell : public AnimatedSprite {
 public:
  explicit Spell(Context const& c, std::string textureName);
  virtual void cast(std::pair<int, int> from, std::pair<int, int> to);
  virtual void tick(float dt);
  virtual void onEvent(const Event& e);
  //  void stop();
 private:
  std::pair<int, int> m_from;
  std::pair<int, int> m_to;
  bool m_casted;
};

#endif
