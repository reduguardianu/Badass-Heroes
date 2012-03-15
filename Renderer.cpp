#include "include/GL/glfw.h"
#include "Renderer.h"
#include "IDrawable.h"
#include "TextureFactory.h"

const float FRAME_SIZE = 32.0f;

Renderer::Renderer():m_window_width(0), 
		     m_window_height(0) {


}

void Renderer::setSize(float w, float h) {
  m_window_width = w;
  m_window_height = h;
}

float Renderer::getWindowWidth() const {
  return m_window_width;
}

float Renderer::getWindowHeight() const {
  return m_window_height;
}

void Renderer::renderSprite(const IDrawable& drawable) {
    Texture t = m_texture_factory.getTexture(drawable.texture());
    glLoadIdentity();
    glTranslatef( 2 * (drawable.x() + 60)  / m_window_width - 1, -2 *  (drawable.y() + 60) / m_window_height + 1, 0.0f);
    glScalef(2 *t.width() * drawable.scaleX() / m_window_width, -2 *t.height() * drawable.scaleY() / m_window_height, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, t.get());
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 0.0f, 0.0f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);

    glEnd();
}

void Renderer::renderSpriteAnimation(const IDrawable& drawable, int frame, ANIM::Direction direction) {
  Texture t = m_texture_factory.getTexture(drawable.texture());
  unsigned int row = static_cast<unsigned int>(direction);
  glLoadIdentity();
    glTranslatef( 2 * (drawable.x() + 60)  / m_window_width - 1, -2 *  (drawable.y() + 60) / m_window_height + 1, 0.0f);
    glScalef(2 * 32 * drawable.scaleX() / m_window_width, -2 * 32 * drawable.scaleY() / m_window_height, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, t.get());
    glBegin(GL_TRIANGLES);
    glTexCoord2f(frame * FRAME_SIZE / t.width() , row * FRAME_SIZE / t.height());
    glVertex3f(-1.0f, 0.0f, 0.1f);

    glTexCoord2f(frame * FRAME_SIZE / t.width(), (row + 1) * FRAME_SIZE / t.height());
    glVertex3f(-1.0f, 1.0f, 0.1f);

    glTexCoord2f((frame + 1) * FRAME_SIZE / t.width(), row * FRAME_SIZE / t.height());
    glVertex3f(0.0f, 0.0f, 0.1f);

    glTexCoord2f(frame * FRAME_SIZE / t.width(), (row + 1) * FRAME_SIZE / t.height());
    glVertex3f(-1.0f, 1.0f, 0.1f);

    glTexCoord2f((frame + 1) * FRAME_SIZE / t.width(), (row + 1) * FRAME_SIZE / t.height());
    glVertex3f(0.0f, 1.0f, 0.1f);

    glTexCoord2f((frame + 1) * FRAME_SIZE / t.width(), row * FRAME_SIZE / t.height());
    glVertex3f(0.0f, 0.0f, 0.1f);


    glEnd();

}

void Renderer::beginFrame() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void Renderer::endFrame() {
  glfwSwapBuffers();
}
