#include "SpriteRenderBehaviour.h"
#include "IRenderer.h"
#include "DisplayObject.h"

SpriteRenderBehaviour::SpriteRenderBehaviour(Frame* frame): m_frame(frame) {
}

void SpriteRenderBehaviour::onRender(IRenderer* renderer, DisplayObject const& display_object) {
  renderer->renderSprite(display_object, m_frame);
}

void SpriteRenderBehaviour::setFrame(Frame* f) {
  m_frame = f;
}
