#ifndef BUTTON_H__
#define BUTTON_H__

#include "Sprite.h"

class Button : public DisplayObject {
 public:
  explicit Button(Context const& c, std::string normal, std::string pressed, std::string selected, std::string text);
  void render();
  void setPressed();
  void setSelected();
  void setNormal();
 private:
  static const int SELECTED;
  static const int PRESSED;
  static const int NORMAL;

  std::string m_text;
  Sprite* m_normal_sprite;
  Sprite* m_pressed_sprite;
  Sprite* m_selected_sprite;
  int m_state;
};

#endif
