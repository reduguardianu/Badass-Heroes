#ifndef FONTFACTORY_H__
#define FONTFACTORY_H__

#include "Font.h"
#include <string>
#include <map>

class FontFactory {
 public:
  static Font* getFont(std::string name);
 private:
  static std::map<std::string, Font*> m_fonts;
};

#endif
