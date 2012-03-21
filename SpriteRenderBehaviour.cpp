#include "SpriteRenderBehaviour.h"
#include "IRenderer.h"
#include "DisplayObject.h"

SpriteRenderBehaviour::SpriteRenderBehaviour(Texture* texture): m_texture(texture) {
}

void SpriteRenderBehaviour::onRender(IRenderer* renderer, DisplayObject const& display_object) {
  renderer->renderSprite(display_object, m_texture);
}
