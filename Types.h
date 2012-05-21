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
  static const std::string spell;
  static const std::string npc_turn_ended;
  static const std::string came;
  static const std::string change_player;
};

class SpellType {
 public:
  static const std::string magic_bullet;
  static const std::string build_wall;
  static const std::string mind_control;
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
