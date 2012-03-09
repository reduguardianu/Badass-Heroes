#include "Sprite.h"
#include "IRenderer.h"

Sprite::Sprite(IRenderer& renderer, std::string textureName):m_renderer(renderer),
                                                             m_texture_name(textureName),
                                                             m_x(0),
                                                             m_y(0),
                                                             m_scale_x(1.0f),
                                                             m_scale_y(1.0f) {
                                                             }

int Sprite::x() const {
    return m_x;
}
int Sprite::y() const {
    return m_y;
}
float Sprite::scaleX() const {
    return m_scale_x;
}
float Sprite::scaleY() const {
    return m_scale_y;
}
const char* Sprite::texture() const {
    return m_texture_name.c_str();
}
void Sprite::render() {
    m_renderer.renderSprite(*this);
}
void Sprite::setPosition(int x, int y) {
    m_x = x;
    m_y = y;
}
void Sprite::setScale(float scale_x, float scale_y) {
    m_scale_x = scale_x;
    m_scale_y = scale_y;
}


