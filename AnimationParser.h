#ifndef ANIMATIONPARSER_H__
#define ANIMATIONPARSER_H__

#include <string>
#include <map>
#include <vector>

typedef std::map<std::string, std::vector<std::pair<float, float> > > AnimationDescription;


class AnimationParser {
 public:
  void parse(std::string filename);
  AnimationDescription m_animations;
  int frame_width;
  int frame_height;
};

#endif
