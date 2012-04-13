#include "AnimationParser.h"
#include <cstdio>
#include <iostream>

void AnimationParser::parse(std::string filename) {
  FILE* file = NULL;
  
  std::string filepath = "../assets/" + filename;
  file = fopen(filepath.c_str(), "r");
  
  fscanf(file, "%d\n", &frame_size);
  
  int animation_count = 0;
  fscanf(file, "%d\n", &animation_count);

  for (int i = 0; i < animation_count; ++i) {
    char name[256];
    fscanf(file, "%s\n", name);

    int frame_count;
    fscanf(file, "%d\n", &frame_count);

    std::vector<std::pair<float, float> > anim;
    for (int j = 0; j < frame_count; ++j) {
      float u;
      float v;
      fscanf(file, "%f %f\n", &u, &v);
      anim.push_back(std::make_pair(u, v));
    }

    m_animations[name] = anim;
  }
}
