#ifndef CHEST_H__
#define CHEST_H__

#include "Sprite.h"

class Chest : public DisplayObject {
 public:
  explicit Chest(Context const& c);
  void open();
  void close();
  void render();
  ~Chest();
 private:
  bool m_is_opened;
  Sprite* m_opened;
  Sprite* m_closed;
};

#endif
