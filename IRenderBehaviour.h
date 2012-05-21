#ifndef IRENDERBEHAVIOUR_H__
#define IRENDERBEHAVIOUR_H__

class DisplayObject;
class IRenderer;

class IRenderBehaviour {
 public:
  virtual void onRender(IRenderer*, DisplayObject const&) = 0;
};

#endif
