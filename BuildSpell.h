#ifndef BUILDSPELL_H__
#define BUILDSPELL_H__

#include "Spell.h"

class BuildSpell : public Spell {
 public:
  explicit BuildSpell(Context const& c);
  void onEvent(const Event& e);
  void tick(float dt);
  void cast(std::pair<int, int> from, std::pair<int, int> to);

};

#endif
