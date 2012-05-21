#ifndef TEXTFIELD_H__
#define TEXTFIELD_H__

#include "DisplayObject.h"
#include <string>

class Textfield : public DisplayObject {
 public:
  explicit Textfield(Context const& c, std::string text, std::string font);
  void render();
 private:
  std::string m_text;
  std::string m_font;
};

#endif
