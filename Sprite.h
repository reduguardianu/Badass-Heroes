#ifndef SPRITE_H__
#define SPRITE_H__
#include <string>
#include "DisplayObject.h"
#include "Context.h"
#include "Texture.h"

class Sprite : public DisplayObject {
public:
  explicit Sprite(Context const& c, std::string textureName);
 private:
    Texture* m_texture;
};

#endif
