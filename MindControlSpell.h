#ifndef MINDCONTROLSPELL_H__
#define MINDCONTROLSPELL_H__

#include "Spell.h"

class MindControlSpell : public Spell {
 public:
  explicit MindControlSpell(Context const& c);
  void onEvent(const Event& e);
  void tick(float dt);
  void cast(std::pair<int, int> from, std::pair<int, int> to);
};

#endif
