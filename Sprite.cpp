#include "Sprite.h"
#include "TextureFactory.h"
#include "SpriteRenderBehaviour.h"
#include "SpriteSizeBehaviour.h"

Sprite::Sprite(Context const& c, std::string textureName): DisplayObject(c) {
  if (textureName.size()) {
    m_texture = TextureFactory::getTexture(textureName);
  }
  m_render_behaviour = new SpriteRenderBehaviour(m_texture);
  m_size_behaviour = new SpriteSizeBehaviour(m_texture);
}





