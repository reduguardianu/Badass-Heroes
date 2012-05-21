#ifndef TEXTURE_H__
#define TEXTURE_H__
#include <string>

class SDL_Surface;

class Texture {
public:
  explicit Texture(std::string name);
  
    int width() const;
    int height() const;
    const char* name() const;
    int numberOfColors() const;
    int redMask() const;
    void* pixels() const;
private:
    SDL_Surface* load(std::string name);
private:
    std::string m_name;
    SDL_Surface* m_texture;
    
};

#endif
