#include "FontFactory.h"

std::map<std::string, Font*> FontFactory::m_fonts;

Font* FontFactory::getFont(std::string name) {
  std::map<std::string, Font*>::const_iterator it = m_fonts.find(name);
  if (it == m_fonts.end()) {
    Font* f = new Font();
    f->load(name);
    m_fonts.insert(std::make_pair(name, f));
    return f;
  }
  else {
    return it->second;
  }
}
