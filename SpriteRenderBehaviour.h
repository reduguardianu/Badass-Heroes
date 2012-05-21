#ifndef SPRITERENDERBEHAVIOUR_H__
#define SPRITERENDERBEHAVIOUR_H__

#include "IRenderBehaviour.h"
#include "Frame.h"


class SpriteRenderBehaviour : public IRenderBehaviour {
 public:
  SpriteRenderBehaviour(Frame* frame);
  virtual void onRender(IRenderer* renderer, DisplayObject const& display_object);
  void setFrame(Frame* f);
 private:
  Frame* m_frame;
};

#endif
