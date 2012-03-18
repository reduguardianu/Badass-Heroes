#ifndef LEVEL_H__
#define LEVEL_H__

#include <string>
#include <vector>
#include "Context.h"
#include "Sprite.h"
#include <map>
#include <vector>
#include "Event.h"
#include "IDrawable.h"
#include "Texture.h"

class Level : public IDrawable  {
 public:
  explicit Level(Context const& c);
  void loadFromFile(std::string filename);
  void render();
  void tick(float dt);
  void onEvent(const Event& e);
  ~Level();

  int x() const;
  int y() const;
  int width() const;
  int height() const;
  float scaleX() const;
  float scaleY() const;
  const Texture* texture() const;
  void setParent(const IDrawable*);
  void addChild(IDrawable*);
 private:
  void initData();
 private:
  std::vector<std::vector<int> > m_data;
  int m_width;
  int m_height;
  Context const& m_context;
  std::map<Keyboard::KEY, bool> m_keys;
  std::vector<IDrawable*> m_children;
  float m_x;
  float m_y;
  float m_scale_x;
  float m_scale_y;
  const IDrawable* m_parent;
};

#endif
