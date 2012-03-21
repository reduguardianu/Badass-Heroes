#ifndef ANIMATEDRENDERBEHAVIOUR_H__
#define ANIMATEDRENDERBEHAVIOUR_H__

#include "IRenderBehaviour.h"
#include "Texture.h"
#include "Types.h"

class AnimatedRenderBehaviour : public IRenderBehaviour {
 public:
  AnimatedRenderBehaviour(Texture*, unsigned int const&, Anim::DIRECTION const&, unsigned int const&);
  void onRender(IRenderer*, DisplayObject const&);
 private:
  Texture* m_texture;
  unsigned int const& m_frame;
  Anim::DIRECTION const& m_direction;
  unsigned int const& m_animation_speed;
};

#endif
