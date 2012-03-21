#ifndef SPRITERENDERBEHAVIOUR_H__
#define SPRITERENDERBEHAVIOUR_H__

#include "IRenderBehaviour.h"
#include "Texture.h"


class SpriteRenderBehaviour : public IRenderBehaviour {
 public:
  SpriteRenderBehaviour(Texture* texture);
  virtual void onRender(IRenderer* renderer, DisplayObject const& display_object);
 private:
  Texture* m_texture;
};

#endif
