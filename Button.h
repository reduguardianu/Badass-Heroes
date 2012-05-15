#ifndef BUTTON_H__
#define BUTTON_H__

#include "Sprite.h"

class Button : public DisplayObject {
 public:
  explicit Button(Context const& c, std::string active, std::string inactive, std::string text);
  void render();
  void setActive(bool value);
 private:
  std::string m_text;
  Sprite* m_active_sprite;
  Sprite* m_inactive_sprite;
  bool m_active;
};

#endif
