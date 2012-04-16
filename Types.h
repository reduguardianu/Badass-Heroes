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

typedef std::pair<int, int> point;

#endif 
