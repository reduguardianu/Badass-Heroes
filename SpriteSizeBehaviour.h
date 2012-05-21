#ifndef SPRITESIZEBEHAVIOUR_H__
#define SPRITESIZEBEHAVIOUR_H__

#include "ISizeBehaviour.h"
#include "Frame.h"

class SpriteSizeBehaviour : public ISizeBehaviour {
 public:
  SpriteSizeBehaviour(Frame*);
  int width() const;
  int height() const;
 private:
  Frame* m_frame;
};

#endif
