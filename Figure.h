#ifndef FIGURE_H__
#define FIGURE_H__

#include "AnimatedSprite.h"

class Figure : public DisplayObject {
 public:
  explicit Figure(Context const& c, std::string headgear, std::string breastplate, std::string pants);
  Figure(const Figure& f);
  void animate(std::string);
  void stop();
  void setDirection(std::string dir);
  void gotoFrame(int frame, int time);
  void tick(float dt);
  void setScale(float value);

  void init(std::string, std::string, std::string);
  std::string headgear() const;
  std::string breastplate() const;
  std::string pants() const;

  ~Figure();
 private:
  std::vector<AnimatedSprite*> m_sprites;
};

#endif
