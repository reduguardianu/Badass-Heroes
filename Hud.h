#ifndef HUD_H__
#define HUD_H__

#include "DisplayObject.h"
#include "AnimatedSprite.h"
#include "Event.h"

class Hud : public DisplayObject {
 public:
  Hud(Context const& c);
  void render();
  void onEvent(const Event& e);
 private:
  std::vector<AnimatedSprite*> m_sprites;
};

#endif
