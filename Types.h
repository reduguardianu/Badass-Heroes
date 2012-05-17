#ifndef TYPES_H__
#define TYPES_H__

#include <utility>
#include <string>

class Animations {
 public: 
  static const std::string up;
  static const std::string down;
  static const std::string left;
  static const std::string right;
  static const std::string idle;
  static const std::string dead;
};

class ET {
 public:
  static const std::string action;
  static const std::string open_chest;
};

namespace State {
  enum STATE {
    Walk = 0,
    Spell = 1,
    Stand = 2
  };
};

typedef std::pair<float, float> point;

class Rectangle {
 public:
  float x;
  float y;
  float width;
  float height;
 Rectangle(float _x, float _y, float _width, float _height):x(_x),y(_y),width(_width),height(_height) {}
};

#endif 
