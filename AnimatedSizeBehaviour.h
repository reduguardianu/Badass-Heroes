#ifndef ANIMATEDSIZEBEHAVIOUR_H__
#define ANIMATEDSIZEBEHAVIOUR_H__

#include "ISizeBehaviour.h"
#include "Texture.h"

class AnimatedSizeBehaviour : public ISizeBehaviour {
 public:
  AnimatedSizeBehaviour(Texture*);
  int width() const;
  int height() const;
 private:
  Texture* m_texture;
};

#endif 
