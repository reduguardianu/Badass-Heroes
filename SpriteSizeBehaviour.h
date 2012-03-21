#ifndef SPRITESIZEBEHAVIOUR_H__
#define SPRITESIZEBEHAVIOUR_H__

#include "ISizeBehaviour.h"
#include "Texture.h"

class SpriteSizeBehaviour : public ISizeBehaviour {
 public:
  SpriteSizeBehaviour(Texture*);
  int width() const;
  int height() const;
 private:
  Texture* m_texture;
};

#endif
